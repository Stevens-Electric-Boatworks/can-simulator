//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.
#include "can/generic/EBPSimDevice.h"

#include <iostream>

#include "can/FrameWriter.h"


void eboat::EBPSimDevice::init() {
    _scheduler.addTask(std::move(std::make_unique<RecurringTask>(
        [this]() {
            send_device_status_frame();
        },
        std::chrono::milliseconds(250) // Device Status Frame
    )));
    _scheduler.addTask(std::move(std::make_unique<RecurringTask>(
        [this]() {
            send_device_version_frame();
        },
        std::chrono::seconds(5) // Device Status Frame
    )));
}

void eboat::EBPSimDevice::tick() {
}

void eboat::EBPSimDevice::send_device_status_frame() const {
    const auto frame = FrameWriter(0x01)
            .u8(device_status.device_state)
            .u8(device_status.board_type)
            .u16(device_status.ms_since_heartbeat)
            .finish();
    _can_io.sendMessage(can_id_, frame);
}

void eboat::EBPSimDevice::send_device_version_frame() const {
    const auto frame = FrameWriter(0x05)
            .u8(version.major)
            .u8(version.minor)
            .u8(version.protocol)
            .u8(version.hardware_rev)
            .finish();
    _can_io.sendMessage(can_id_, frame);
}
