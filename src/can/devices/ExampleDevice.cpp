//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can/devices/ExampleDevice.h"

#include "can/FrameWriter.h"

void eboat::device::ExampleDevice::init() {
    EBPSimDevice::init(); // NEEDED!!
    _scheduler.addTask(std::move(std::make_unique<RecurringTask>(
        [this]() {
            send_temp_sensor_frame();
        },
        std::chrono::milliseconds(250) // Device Status Frame
    )));

}

void eboat::device::ExampleDevice::tick() {
    EBPSimDevice::tick(); // NEEDED!!
}

void eboat::device::ExampleDevice::send_temp_sensor_frame() {
    const auto frame = FrameWriter(0x10)
            .u16(temp_a.next())
            .u16(temp_b.next())
            .u16(temp_c.next())
            .finish();
    _can_io.sendMessage(can_id_, frame);
}
