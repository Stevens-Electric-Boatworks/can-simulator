//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.
#pragma once
#include "GUIStateManager.h"
#include "can_simulator/can/SimManager.h"

namespace eboat::gui {
    class GUIManager {
    public:
        explicit GUIManager(SimManger &sim) : gui_state_(GUIStateManager{sim}) {}

        void run();

    private:
        void run_loop_();

        GUIStateManager gui_state_;
        std::unique_ptr<std::thread> thread_;
    };
}
