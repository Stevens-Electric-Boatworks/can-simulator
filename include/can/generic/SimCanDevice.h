//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once

namespace eboat
{
    class SimCanDevice
    {
    public:
        virtual ~SimCanDevice() = default;
        virtual void tick() = 0;
    };
}

