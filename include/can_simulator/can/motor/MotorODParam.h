//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <cstdint>

namespace eboat
{
    /**
     * Defines a CAN SDO Read that can be used on the motor
     */
    enum class ODType { U8, U16, U32, I8, I16, I32, PDO_UNKNOWN };

    struct MotorODParam {
        std::uint16_t index;
        uint8_t subindex;
        ODType type;

        bool operator==(const MotorODParam &other) const {
            return index == other.index && subindex == other.subindex;
        }

        friend std::size_t hash_value(const MotorODParam &obj) {
            std::size_t seed = 0x216DD4C1;
            seed ^= (seed << 6) + (seed >> 2) + 0x360C5B1B +
                    static_cast<std::size_t>(obj.index);
            seed ^= (seed << 6) + (seed >> 2) + 0x50EC5801 +
                    static_cast<std::size_t>(obj.subindex);
            return seed;
        }
    };

}
