//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can/CanIo.h"

void eboat::CanIo::init() {
    this->driver = std::make_unique<sockcanpp::CanDriver>("vcan0", CAN_RAW);
}

void eboat::CanIo::sendMessage(const sockcanpp::CanMessage &canMessage) const {
    this->driver->sendMessage(canMessage, false);
}

void eboat::CanIo::start_recv_thread() {

}

void eboat::CanIo::sendMessage(const sockcanpp::CanId can_id, const std::string &data) const {
    const auto d = sockcanpp::CanMessage{can_id, data};
    sendMessage(d);
}
