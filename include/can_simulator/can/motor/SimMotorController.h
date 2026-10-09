//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <string>
#include <utility>

#include "CANSlave.h"
#include "MotorODParam.h"


namespace eboat
{
    /**
    * Represents a simulated motor controller
    */
    class SimMotorController
    {
    public:
        const std::string name;
        const int8_t id;
        std::vector<MotorODParam> default_od_params_;
        /**
         *
         * @param name Human name of the motor controller
         * @param id CAN ID of the motor controller
         * @param timer Lely timer object
         * @param chan Lely can channel
         * @param eds_path The path of the slave .eds file
         * @param default_od_params The default object dictionary parameters that will also be shown in the GUI
         */
        SimMotorController(std::string name, const int8_t id, lely::io::Timer timer,
                           lely::io::CanChannel chan, const std::string& eds_path, std::vector<MotorODParam> default_od_params)
            : name(std::move(name)),
              channel_(std::move(chan)),
              timer_(std::move(timer)),
              id(id), default_od_params_(std::move(default_od_params))
        // use `id`, not `id_`; see below

        {
            this->can_slave_ = std::make_unique<CANSlave>(timer_, channel_, eds_path, id);
        }

        void init(const lely::io::CanController& can_controller);

        /**
         * Performs a thread-safe write into the motors local object dictionary.
         */
        template <typename T>
        void SafeWrite(uint16_t index, uint8_t subindex, T value)
        {
            this->can_slave_->SafeWrite(index, subindex, value);
        }

        [[nodiscard]] CANSlave& getLelyCANSlave() const
        {
            return *can_slave_;
        }

        [[nodiscard]] lely::io::CanChannel& getChannel()
        {
            return channel_;
        }

    private:
        lely::io::Timer timer_;
        std::unique_ptr<CANSlave> can_slave_;
        lely::io::CanChannel channel_;
    };
}
