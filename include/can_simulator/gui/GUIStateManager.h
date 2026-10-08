//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "can_simulator/can/SimManager.h"

namespace eboat::gui {
    static int MOTOR_A = 0;
    static int MOTOR_B = 1;
    class GUIStateManager {
    public:
        explicit GUIStateManager(SimManger &sim)
            : sim(sim) {
        }

        template<typename T>
        T get(const int motor, const uint16_t idx, const uint8_t subidx) {
            return sim.getMotor(motor).getLelyCANSlave().Read<T>(idx, subidx);
        }
        template<typename T>
        void set(const int motor, const uint16_t idx, const uint8_t subidx, T value) {
            sim.getMotor(motor).getLelyCANSlave().Write<T>(idx, subidx, value);
        }

    private:
        SimManger& sim;
    };
}
