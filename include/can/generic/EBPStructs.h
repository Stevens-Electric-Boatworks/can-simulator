//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <cstdint>

namespace eboat {

    //Device State Constants
    #define DEV_STATE_INIT 0
    #define DEV_STATE_OPERATIONAL 1
    #define DEV_STATE_INACTIVE 2
    #define DEV_STATE_UNKNOWN 3

    // Board Type Constants
    #define BOARD_UNKNOWN 0
    #define BOARD_COOLING 1
    #define BOARD_POWER 2
    #define BOARD_DASH 3

    struct EBPDeviceStatus {
        uint8_t device_state;
        uint8_t board_type;
        uint16_t seconds_since_boot;
        uint16_t ms_since_heartbeat;

        EBPDeviceStatus(const uint8_t device_state, const uint8_t board_type, const uint16_t seconds_since_boot,
                        const uint16_t ms_since_heartbeat)
            : device_state(device_state),
              board_type(board_type),
              seconds_since_boot(seconds_since_boot),
              ms_since_heartbeat(ms_since_heartbeat) {
        }
    };

    struct EBPFirmwareVersion {
        uint8_t major;
        uint8_t minor;
        uint8_t protocol;
        uint8_t hardware_rev;

        EBPFirmwareVersion(const uint8_t major, const uint8_t minor, const uint8_t protocol, const uint8_t hardware_rev)
            : major(major),
              minor(minor),
              protocol(protocol),
              hardware_rev(hardware_rev) {
        }
    };
}
