//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/can/motor/SimMotorController.h"

void eboat::SimMotorController::init(const lely::io::CanController& can_controller)
{
    std::printf("Initializing Motor %d\n", id);
    getChannel().open(can_controller);
    SafeWrite(0x2030, 3, static_cast<int16_t>(120));
    SafeWrite(0x2030, 2, static_cast<int16_t>(670));
    SafeWrite(0x2040, 3, static_cast<int16_t>(12));
    SafeWrite(0x2071, 2, static_cast<int16_t>(-32767));
    getLelyCANSlave().Reset();
}
