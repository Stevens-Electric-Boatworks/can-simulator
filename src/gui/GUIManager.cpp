//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/gui/GUIManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <hello_imgui/hello_imgui.h>


void eboat::gui::GUIManager::run() {
    thread_ = std::make_unique<std::thread>([this]() {
        auto guiFunction = [this]() {
            if (ImGui::Begin("Motor A Values Adjustment"), 0, ImGuiWindowFlags_AlwaysAutoResize) {
                if (ImGui::BeginTabBar("Motor A Valeu Adjustment"), ImGuiTabBarFlags_Reorderable) {
                    if (ImGui::BeginTabItem("0x2030 (DCBus)")) {
                        int v  = this->gui_state_.get<int16_t>(MOTOR_A, 0x2030, 2);
                        int x  = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 5);
                        if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))     gui_state_.set<int16_t>(MOTOR_A, 0x2030, 2, v);
                        if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000)) gui_state_.set<int16_t>(MOTOR_A, 0x2030, 5, x);
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("0x2031 (DCBus3)")) {
                        int v  = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 2);
                        int x  = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 5);
                        if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))     gui_state_.set<int16_t>(MOTOR_A, 0x2030, 2, v);
                        if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000)) gui_state_.set<int16_t>(MOTOR_A, 0x2030, 5, x);
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
            }
            ImGui::End();
            if (ImGui::Begin("Motor B Values Adjustment"), 0, ImGuiWindowFlags_AlwaysAutoResize) {
                if (ImGui::BeginTabBar("Motor B Valeu Adjustment"), ImGuiTabBarFlags_Reorderable) {
                    if (ImGui::BeginTabItem("0x2030 (DCBus)")) {
                        int v  = this->gui_state_.get<int16_t>(MOTOR_B, 0x2030, 2);
                        int x  = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 5);
                        if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))     gui_state_.set<int16_t>(MOTOR_B, 0x2030, 2, v);
                        if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000)) gui_state_.set<int16_t>(MOTOR_B, 0x2030, 5, x);
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("0x2031 (DCBus2")) {
                        int v  = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 2);
                        int x  = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 5);
                        if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))     gui_state_.set<int16_t>(MOTOR_B, 0x2030, 2, v);
                        if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000)) gui_state_.set<int16_t>(MOTOR_B, 0x2030, 5, x);
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
            }

            ImGui::End();
    };



        HelloImGui::Run(guiFunction, "Stevens Electric Boatworks | CANOpen Simulator");
    });

}