//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can/sensors/ExampleSensor.h"

std::pmr::string eboat::ExampleSensor::get_name() {
    return "Cooling Loop Sensor";
}

std::unique_ptr<eboat::SimSensorSource<eboat::data_type>> & eboat::ExampleSensor::get_sensor_source() {
    return source;
}

eboat::data_type eboat::ExampleSensor::next() {
    return source->next();
}
