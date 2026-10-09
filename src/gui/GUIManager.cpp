//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/gui/GUIManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <hello_imgui/hello_imgui.h>


void eboat::gui::GUIManager::run()
{
    thread_ = std::make_unique<std::thread>([this]()
    {
        auto guiFunction = [this]()
        {
            if (ImGui::Begin("Object Dictionary Adjustment"), ImGuiWindowFlags_AlwaysAutoResize)
            {
                ImGui::Text("Motor A");
                drawMotorODParameters();

                ImGui::End();
            }

            if (ImGui::Begin("Lely Status"), ImGuiWindowFlags_AlwaysAutoResize)
            {
                ImGui::Text("Motor A");
                if (ImGui::BeginChild("Motor A Lely Status"))
                {
                    ImGui::EndChild();
                }
                ImGui::Separator();
                ImGui::Text("Motor B");

                ImGui::End();
            }
        };


        HelloImGui::Run(guiFunction, "Stevens Electric Boatworks | CANOpen Simulator");
    });
}

void eboat::gui::GUIManager::drawMotorODParameters()
{
    if (ImGui::BeginChild("Motor A OD Adjustment"))
    {
        if (ImGui::BeginTabBar("Motor A OD Adjustment Tab"), ImGuiTabBarFlags_Reorderable)
        {
            if (ImGui::BeginTabItem("0x2030 (DCBus)"))
            {
                int v = this->gui_state_.get<int16_t>(MOTOR_A, 0x2030, 2);
                int x = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 5);
                if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_A, 0x2030, 2, v);
                if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_A, 0x2030, 5, x);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("0x2031 (DCBus3)"))
            {
                int v = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 2);
                int x = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 5);
                if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_A, 0x2030, 2, v);
                if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_A, 0x2030, 5, x);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::Separator();
        ImGui::Text("Motor B");
        if (ImGui::BeginTabBar("Motor B OD Adjustment TabBar"), ImGuiTabBarFlags_Reorderable)
        {
            if (ImGui::BeginTabItem("0x2030 (DCBus)"))
            {
                int v = this->gui_state_.get<int16_t>(MOTOR_B, 0x2030, 2);
                int x = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 5);
                if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_B, 0x2030, 2, v);
                if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_B, 0x2030, 5, x);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("0x2031 (DCBus2"))
            {
                int v = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 2);
                int x = gui_state_.get<int16_t>(MOTOR_B, 0x2030, 5);
                if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_B, 0x2030, 2, v);
                if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000))
                    gui_state_.set<int16_t>(
                        MOTOR_B, 0x2030, 5, x);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
}
