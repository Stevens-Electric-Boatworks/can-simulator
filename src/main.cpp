#include "sockcanpp/CanDriver.hpp"
#include "sockcanpp/CanMessage.hpp"
//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.
int main(int argc, char* argv[]) {
    // Your program logic here

    sockcanpp::CanDriver cDriver{"vcan0", CAN_RAW}; // No default sender ID
    sockcanpp::CanMessage msg{0x10, "\x10\x2F\x3D\x04\x05\x06\x07\x08"};
    while (true)
    {
        cDriver.sendMessage(msg, false);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}