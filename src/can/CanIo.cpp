//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can/CanIo.h"
#include "iostream"
#include "ByteHelpers.h"

void eboat::CanIo::init() {
    this->driver = std::make_unique<sockcanpp::CanDriver>("vcan0", CAN_RAW);
}

void eboat::CanIo::sendMessage(const sockcanpp::CanMessage &canMessage) const {
    this->driver->sendMessage(canMessage, false);
}

long eboat::CanIo::get_ms_since_last_heartbeat() const
{
    return get_current_time_in_ms() - last_heartbeat;
}

void eboat::CanIo::start_recv_thread() {
    this->active = true;
    this->msg_poll_thread = std::thread([this]
    {
        while (this->active)
        {
            try
            {
                if (!this->driver->waitForMessages(std::chrono::milliseconds(20)))
                {
                    continue;
                }
                if (const auto msg = driver->readMessage(); msg.isErrorFrame())
                {
                    //ignore error frames
                }
                else
                {
                    handleFrame(msg);
                }
            }
            catch (std::exception& e)
            {
                std::cerr << "CAN receive error: " << e.what() << '\n'; //TODO: add proper ROS logging
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    });
}

void eboat::CanIo::handleFrame(const sockcanpp::CanMessage& msg)
{
    // Controls PC Message
    if (msg.getCanId() == 0x01)
    {
        const auto data = msg.getFrameData();
        // Heartbeat byte
        if (can::readU16(msg.getFrameData(), 0) == 0x00)
        {
            //validate byte
            if (can::readU16(data, 1) == 0x12 &&
                can::readU16(data, 2) == 0x34 &&
                can::readU16(data, 3) == 0x56 &&
                can::readU16(data, 4) == 0x78 &&
                can::readU16(data, 5) == 0x9A &&
                can::readU16(data, 6) == 0xBC &&
                can::readU16(data, 7) == 0xDE)
            {
                last_heartbeat = get_current_time_in_ms();
            }

        }
    }
}

long eboat::CanIo::get_current_time_in_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void eboat::CanIo::sendMessage(const sockcanpp::CanId can_id, const std::string &data) const {
    const auto d = sockcanpp::CanMessage{can_id, data};
    sendMessage(d);
}
