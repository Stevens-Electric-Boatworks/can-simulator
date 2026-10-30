//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include "EBPStructs.h"
#include "SimCanDevice.h"
#include "TaskScheduler.h"

namespace eboat {
    class EBPSimDevice : public SimCanDevice {
    public:
        explicit EBPSimDevice(const uint8_t can_id, const uint8_t board_type, const EBPFirmwareVersion version, TaskScheduler &scheduler, CanIo& can_io)
            : SimCanDevice(can_id, scheduler, can_io), device_status(EBPDeviceStatus{DEV_STATE_INIT, board_type, 0, 500}), version(version) {
        }

        void init() override;

        void tick() override;

    protected:
        EBPDeviceStatus device_status;
        EBPFirmwareVersion version;

        //TODO: implement genric EBP headers
    private:
        void send_device_status_frame() const;
        void send_device_version_frame() const;

    };
}
