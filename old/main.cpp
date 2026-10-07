#include <iostream>
#include <lely/ev/loop.hpp>
#if _WIN32
#include <lely/io2/win32/ixxat.hpp>
#include <lely/io2/win32/poll.hpp>
#elif defined(__linux__)
#include <lely/io2/linux/can.hpp>
#include <lely/io2/posix/poll.hpp>
#else
#error This file requires Windows or Linux.
#endif
#include <lely/io2/sys/io.hpp>
#include <lely/io2/sys/sigset.hpp>
#include <lely/io2/sys/timer.hpp>
#include <lely/coapp/slave.hpp>

// UDP / threading
#include <thread>
#include <atomic>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>

#if _WIN32
#include <thread>
#endif

using namespace lely;

// ── UDP configuration ────────────────────────────────────────────────────────
static constexpr uint16_t UDP_PORT = 5005; // must match Simulink's "Remote port"
static constexpr size_t UDP_BUF_SIZE = 256; // bytes – enlarge if Simulink sends more signals

// ── Object-dictionary placeholder ───────────────────────────────────────────
// Replace these with your real indices/sub-indices.
// Simulink typically sends doubles (8 bytes each); adjust the type to match
// whatever signal type your EDS actually maps.
static constexpr uint16_t OD_INDEX_1 = 0x2030; // ← replace
static constexpr uint8_t OD_SUBINDEX_1 = 3; // ← replace
// add more as needed …


// ── Slave ────────────────────────────────────────────────────────────────────
class MySlave : public canopen::BasicSlave
{
public:
    MySlave(lely::io::Timer& timer,
            lely::io::CanChannel& chan,
            const std::string& eds,
            uint8_t node_id)
        : canopen::BasicSlave(timer, chan, eds, "", node_id)
    {
    }

    // Thread-safe helper: write a value into the OD from any thread.
    // Lely's Write() is NOT thread-safe by itself, so we guard it.
    template <typename T>
    void SafeWrite(uint16_t index, uint8_t subindex, T value)
    {
        std::lock_guard<std::mutex> lock(od_mutex_);
        Write(index, subindex, value);
    }

private:
    std::mutex od_mutex_;
};


// ── UDP receiver thread ───────────────────────────────────────────────────────
//
// Simulink's "UDP Send" block sends a packed binary payload.  By default it
// uses native double (float64) for every signal.  The layout below assumes:
//
//   bytes  0-7  → signal 1  (double)
//   bytes  8-15 → signal 2  (double)
//   …
//
// Adjust the struct / memcpy section to match your actual Simulink bus layout.

struct SimulinkPacket
{
    double signal1; // ← rename / retype to match your Simulink outport
};

void udp_receiver_thread(MySlave& slave, std::atomic<bool>& running)
{
    // ── open socket ──────────────────────────────────────────────────────────
    int sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::perror("UDP socket");
        return;
    }

    // Allow rapid restart without "Address already in use"
    int opt = 1;
    ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Set a receive timeout so the thread can check `running` periodically
    struct timeval tv{.tv_sec = 1, .tv_usec = 0};
    ::setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(UDP_PORT);

    if (::bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        std::perror("UDP bind");
        ::close(sock);
        return;
    }

    std::printf("[UDP] Listening on port %u\n", UDP_PORT);

    uint8_t buf[UDP_BUF_SIZE];

    while (running.load())
    {
        ssize_t n = ::recv(sock, buf, sizeof(buf), 0);

        if (n < 0)
        {
            // EAGAIN / EWOULDBLOCK just means the 1-second timeout fired
            continue;
        }

        if (static_cast<size_t>(n) < sizeof(SimulinkPacket))
        {
            std::fprintf(stderr,
                         "[UDP] Short packet: got %zd bytes, expected %zu\n",
                         n, sizeof(SimulinkPacket));
            continue;
        }

        // ── Unpack Simulink payload ──────────────────────────────────────
        SimulinkPacket pkt{};
        std::memcpy(&pkt, buf, sizeof(pkt));

        std::printf("[UDP] signal1=%.4f  signal2=%.5f\n",
                    pkt.signal1);
        slave.SafeWrite<int16_t>(OD_INDEX_1, OD_SUBINDEX_1,
                                 static_cast<int16_t>(std::abs(pkt.signal1 * 1000)));
    }
    ::close(sock);
    std::printf("[UDP] Receiver thread exiting.\n");
}


int main()
{
    io::Context ctx;
    io::Poll poll(ctx);
    ev::Loop loop(poll.get_poll());
    auto exec = loop.get_executor();

    io::Timer timer(poll, exec, CLOCK_REALTIME);
    io::CanController ctrl("vcan0");
    io::CanChannel chan(poll, exec);
    chan.open(ctrl);

    MySlave slave(timer, chan, "/home/isayal/motors.eds", 6);

    // ── Signal handler ───────────────────────────────────────────────────────
    io::SignalSet sigset(poll, exec);
    sigset.insert(SIGHUP);
    sigset.insert(SIGINT);
    sigset.insert(SIGTERM);

    std::atomic<bool> udp_running{true};

    sigset.submit_wait([&](int /*signo*/)
    {
        sigset.clear();
        udp_running.store(false); // tell the UDP thread to stop
        ctx.shutdown();
    });

    // ── Start UDP thread ─────────────────────────────────────────────────────
    std::thread udp_thread(udp_receiver_thread,
                           std::ref(slave),
                           std::ref(udp_running));

    slave.Reset();
    slave.Write(0x2030, 3, static_cast<int16_t>(120));
    slave.Write(0x2030, 2, static_cast<int16_t>(670));
    slave.Write(0x2040, 3, static_cast<int16_t>(12));
    slave.Write(0x2071, 2, static_cast<int16_t>(-32767));

    std::printf("Node ID : %u\n", slave.id());
    std::printf("Net ID  : %u\n", slave.netid());
    // std::printf("Test read 0x2030/2 : %d\n", slave.Read<int16_t>(0x2030, 2));
    // std::printf("Test read 0x2040/3 : %d\n", slave.Read<int16_t>(0x2040, 11));

    loop.run(); // blocks until ctx.shutdown()

    udp_running.store(false);
    udp_thread.join();

    return 0;
}
