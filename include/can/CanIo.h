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
    private:
        std::unique_ptr<sockcanpp::CanDriver> driver = nullptr;
    };
}
