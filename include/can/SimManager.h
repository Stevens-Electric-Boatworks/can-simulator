//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "generic/SimCanDevice.h"

namespace eboat
{
    class SimManager
    {
    public:
        void register_device(std::unique_ptr<SimCanDevice> device);

        TaskScheduler& init_scheduler();

        void start() const;

    private:
        std::vector<std::unique_ptr<SimCanDevice>> devices;
        std::unique_ptr<TaskScheduler> scheduler_;
    };
}
