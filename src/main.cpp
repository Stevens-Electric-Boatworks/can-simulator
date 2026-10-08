//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/can/SimManager.h"
#include "can_simulator/gui/GUIManager.h"

int main()
{
    auto simulator = std::make_unique<eboat::SimManger>();
    simulator->createNewMotorController("Motor A", 6);
    simulator->createNewMotorController("Motor B", 7);
    simulator->startLely();
    printf("Started Lely background thread.\n");
    auto& lely = simulator->getBackgroundThread();

    const auto gui = std::make_unique<eboat::gui::GUIManager>(*simulator);
    gui->run();

    lely.join();


}
