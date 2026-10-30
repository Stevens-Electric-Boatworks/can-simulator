//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "can/generic/SimSensorSource.h"

namespace eboat
{
    template <typename T>
    class RandomSimSensorSource: public SimSensorSource<T>
    {
    public:
        T next() {
            //TODO add a proper random gen
            return -5;
        }
    };
}
