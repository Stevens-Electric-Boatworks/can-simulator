//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <string>
#include <utility>

#include "CANSlave.h"


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
        /**
         *
         * @param name Human name of the motor controller
         * @param id CAN ID of the motor controller
         * @param timer Lely timer object
         * @param chan Lely can channel
         * @param eds_path The path of the slave .eds file
         */
        SimMotorController(std::string name, const int8_t id, lely::io::Timer timer,
                           lely::io::CanChannel chan, const std::string& eds_path)
            : name(std::move(name)),
              channel_(std::move(chan)),
              timer_(std::move(timer)),
              id(id) // use `id`, not `id_`; see below

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
