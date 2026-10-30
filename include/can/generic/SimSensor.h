//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <memory>
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
        virtual std::unique_ptr<SimSensorSource<T>>& get_sensor_source() = 0;
        virtual T next() = 0;
    };
}
