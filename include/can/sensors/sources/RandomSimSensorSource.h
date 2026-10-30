//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "can/generic/SimSensorSource.h"

namespace eboat
{
    template <typename T>
    class RandomSimSensorSource: SimSensorSource<T>
    {
    public:
        T next() override;
    };
}
