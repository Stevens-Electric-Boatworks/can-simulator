//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "SimCanDevice.h"

namespace eboat
{
    class EBPSimDevice: public SimCanDevice
    {
    public:
        void tick() override;

        //TODO: implement genric EBP headers
    };
}
