#include "can/CanIo.h"
#include "can/SimManager.h"
#include "can/devices/ExampleDevice.h"
#include "sockcanpp/CanDriver.hpp"
#include "sockcanpp/CanMessage.hpp"
//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.
int main(int argc, char* argv[]) {
    auto io = eboat::CanIo();
    io.init();
    auto manager = eboat::SimManager();
    auto& scheduler = manager.init_scheduler();
    manager.register_device(std::make_unique<eboat::device::ExampleDevice>(0x10, BOARD_COOLING, eboat::EBPFirmwareVersion{0, 1, 1, 1}, scheduler, io));
    manager.start();
    std::this_thread::sleep_for(std::chrono::seconds(30));

    // Stop the scheduler
    scheduler.stop();
    return 0;
}