//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "TaskScheduler.h"
#include "can/CanIo.h"

namespace eboat
{
    class SimCanDevice
    {
    public:
        explicit SimCanDevice(const uint8_t can_id, TaskScheduler &scheduler, CanIo& can_io)
            : _scheduler(scheduler), _can_io(can_io), can_id_(can_id) {
        }

        virtual ~SimCanDevice() = default;
        virtual void init() = 0;
        virtual void tick() = 0;
    protected:
        TaskScheduler& _scheduler;
        CanIo& _can_io;
        uint8_t can_id_;
    };
}

