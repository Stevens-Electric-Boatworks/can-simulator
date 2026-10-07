//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/can/SimManager.h"
#include <memory>
#include <lely/util/diag.h>


eboat::SimManger::SimManger()
{
    lely_ctx = std::make_unique<lely::io::Context>();
    this->lely_poll = std::make_unique<lely::io::Poll>(*lely_ctx);
    // Create a polling event loop and pass it the platform-independent polling
    // interface. If no tasks are pending, the event loop will poll for I/O
    // events.
    lely_loop = std::make_unique<lely::ev::Loop>(lely_poll->get_poll());
    // Create a timer using a monotonic clock, i.e., a clock that is not affected
    // by discontinuous jumps in the system time.
    lely_controller = std::make_unique<lely::io::CanController>("vcan0");
}

eboat::SimMotorController& eboat::SimManger::createNewMotorController(std::string name, int8_t id)
{
    auto timer = lely::io::Timer(*lely_poll, lely_loop->get_executor(), CLOCK_MONOTONIC);
    auto channel = lely::io::CanChannel(*lely_poll, lely_loop->get_executor());
    motor_controllers_.push_back(
        std::make_unique<SimMotorController>(std::move(name), id, std::move(timer), std::move(channel),
                                             "/home/isayal/motors.eds"));
    return *motor_controllers_.back();
}

void eboat::SimManger::startLely()
{
    for (const auto& motor : this->motor_controllers_)
    {
        motor->init(*this->lely_controller);
        printf("Reset Motor %d\n", motor->id);
    }

    this->lely_background_loop_thread_ = std::make_unique<std::thread>([this]
    {
        this->lely_loop->run();
    });;
}
