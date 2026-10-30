//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once

namespace eboat
{
    template <typename T>
    class SimSensorSource
    {
    public:
        virtual ~SimSensorSource() = default;
        virtual T next() = 0;
    };
}
