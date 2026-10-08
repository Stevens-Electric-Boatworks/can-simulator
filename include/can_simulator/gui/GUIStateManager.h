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

        [[nodiscard]] unsigned long getMotorCount() const
        {
            return sim.getMotorCount();
        }
        std::unordered_map<uint16_t, std::vector<MotorODParam>> getODParameters(const int motor_index)
        {
            auto od_map = std::unordered_map<uint16_t, std::vector<MotorODParam>>();

            auto motor_od = sim.getMotor(motor_index).default_od_params_;
        }

        template<typename T>
        T get(const int motor_index, const uint16_t idx, const uint8_t subidx) {
            return sim.getMotor(motor_index).getLelyCANSlave().Read<T>(idx, subidx);
        }
        template<typename T>
        void set(const int motor_index, const uint16_t idx, const uint8_t subidx, T value) {
            sim.getMotor(motor_index).getLelyCANSlave().SafeWrite<T>(idx, subidx, value);
        }

    private:
        SimManger& sim;
    };
}
