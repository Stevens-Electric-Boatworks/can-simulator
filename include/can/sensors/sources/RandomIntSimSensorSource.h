//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "can/generic/SimSensorSource.h"
#include "random"

namespace eboat
{
    class RandomIntSimSensorSource: public SimSensorSource<int>
    {
    public:
        RandomIntSimSensorSource(const int low, const int high)
                    : low(low),
                      high(high)
        {
        }
        int next() override
        {
            return dist(gen);
        }
    private:
        std::random_device rd;
        std::mt19937 gen{rd()};
        const int low;
        const int high;
        std::uniform_int_distribution<> dist {low, high};
    };
}
