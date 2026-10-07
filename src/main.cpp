//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/can/SimManager.h"

int main()
{
    auto simulator = std::make_unique<eboat::SimManger>();
    simulator->createNewMotorController("Motor A", 6);
    simulator->createNewMotorController("Motor B", 7);
    simulator->startLely();
    printf("Started Lely background thread.\n");
    simulator->getBackgroundThread().join();
    printf("Ended background thread.\n");
}
