//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "can/generic/EBPSimDevice.h"
#include "can/sensors/ExampleSensor.h"

namespace eboat::device {
    class ExampleDevice: public EBPSimDevice {
    public:
        ExampleDevice(uint8_t can_id, uint8_t board_type, const EBPFirmwareVersion &version, TaskScheduler &scheduler,
            CanIo &can_io)
            : EBPSimDevice(can_id, board_type, version, scheduler, can_io) {
        }

        void init() override;

        void tick() override;

    private:
        void send_temp_sensor_frame();

        ExampleSensor temp_a = ExampleSensor();
        ExampleSensor temp_b = ExampleSensor();
        ExampleSensor temp_c = ExampleSensor();

    };
}
