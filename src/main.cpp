//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/can/SimManager.h"
#include "can_simulator/gui/GUIManager.h"

int main()
{
    auto simulator = std::make_unique<eboat::SimManger>();
    auto default_od = {
        eboat::MotorODParam{
            .index = 0x2030,
            .subindex = 2,
            .type = eboat::ODType::I16
        },
        eboat::MotorODParam{
            .index = 0x2030,
            .subindex = 3,
            .type = eboat::ODType::I16
        },
        eboat::MotorODParam{
            .index = 0x2031,
            .subindex = 3,
            .type = eboat::ODType::I16
        },
    };
    simulator->createNewMotorController("Motor A", 6, default_od);
    simulator->createNewMotorController("Motor B", 7, default_od);
    simulator->startLely();
    printf("Started Lely background thread.\n");
    auto& lely = simulator->getBackgroundThread();

    const auto gui = std::make_unique<eboat::gui::GUIManager>(*simulator);
    gui->run();

    lely.join();


}
