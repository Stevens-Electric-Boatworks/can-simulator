//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <lely/ev/loop.hpp>
#include <lely/io2/posix/poll.hpp>

#include "motor/SimMotorController.h"


namespace eboat
{
    class SimManger
    {
    public:
        SimManger();

        SimMotorController& createNewMotorController(std::string name, int8_t id, const std::vector<MotorODParam>& default_od_params);
        void startLely();

        [[nodiscard]] std::thread& getBackgroundThread() const
        {
            return *this->lely_background_loop_thread_;
        }

        SimMotorController &getMotor(int motor) const;
        unsigned long getMotorCount() const;

    private:
        std::vector<std::unique_ptr<SimMotorController>> motor_controllers_ = {};
        std::unique_ptr<lely::io::Context> lely_ctx;
        std::unique_ptr<lely::io::Poll> lely_poll;
        std::unique_ptr<lely::ev::Loop> lely_loop;
        std::unique_ptr<lely::io::CanController> lely_controller;

        std::unique_ptr<std::thread> lely_background_loop_thread_;
    };
}
