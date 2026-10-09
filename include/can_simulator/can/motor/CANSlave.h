//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <lely/coapp/slave.hpp>
#include <lely/io2/linux/can.hpp>
#include <lely/io2/sys/timer.hpp>

class CANSlave : public lely::canopen::BasicSlave
{
public:
    CANSlave(lely::io::Timer& timer,
             lely::io::CanChannel& chan,
             const std::string& eds,
             const uint8_t node_id)
        : BasicSlave(timer, chan, eds, "", node_id)
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
    std::mutex od_mutex_ = {};
};
