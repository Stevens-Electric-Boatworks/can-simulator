//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "sockcanpp/CanDriver.hpp"

namespace eboat
{
    class CanIo
    {
    public:
        void init();
        void start_recv_thread();
        void sendMessage(sockcanpp::CanId can_id, const std::string& data) const;
        void sendMessage(const sockcanpp::CanMessage& canMessage) const;
        [[nodiscard]] long get_ms_since_last_heartbeat() const;

    private:
        void handleFrame(const sockcanpp::CanMessage& msg);
        static long get_current_time_in_ms();


        long last_heartbeat = get_current_time_in_ms();
        std::unique_ptr<sockcanpp::CanDriver> driver = nullptr;
        bool active{false};
        std::thread msg_poll_thread;
    };
}
