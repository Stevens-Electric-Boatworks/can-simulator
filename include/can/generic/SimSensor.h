//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <string>
#include <vector>

#include "SimSensorSource.h"

namespace eboat
{
    template <typename T>
    class SimSensor
    {
    public:
        virtual ~SimSensor() = default;
        virtual std::pmr::string get_name() = 0;
        virtual SimSensorSource<T> get_sensor_source() = 0;
    };
}
