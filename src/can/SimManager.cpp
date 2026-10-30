//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.
#include "can/SimManager.h"

void eboat::SimManager::register_device(std::unique_ptr<SimCanDevice> device) {
    devices.emplace_back(std::move(device));
}

TaskScheduler &eboat::SimManager::init_scheduler() {
    scheduler_ = std::make_unique<TaskScheduler>();
    return *scheduler_;
}

void eboat::SimManager::start() const {
    for (const auto &device: devices) {
        device->init();
    }
    auto recurringTask = std::make_unique<RecurringTask>(
        [this]() {
            for (const auto &device: devices) {
                device->tick();
            }
        },
        std::chrono::milliseconds(50) // 20hz
    );
    scheduler_->addTask(std::move(recurringTask));
}
