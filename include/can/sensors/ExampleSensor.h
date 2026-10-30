//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <cstdint>

#include "can/generic/SimSensor.h"
#include "sources/RandomSimSensorSource.h"

namespace eboat {
    /**
     * This example sensor will be a cooling loop sensor
     */
    using data_type = uint16_t;
    class ExampleSensor: public SimSensor<data_type> {
    public:
        ExampleSensor() {
            source = std::make_unique<RandomSimSensorSource<data_type>>();
        }

        std::pmr::string get_name() override;

        std::unique_ptr<SimSensorSource<data_type>>& get_sensor_source() override;

        data_type next() override;

    private:
        std::unique_ptr<SimSensorSource<data_type>> source;
    };
}
