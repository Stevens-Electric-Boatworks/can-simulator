//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#include "can_simulator/gui/GUIManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>


void eboat::gui::GUIManager::run() {

    thread_ = std::make_unique<std::thread>([this]() {
        this->run_loop_();
    });

}

void eboat::gui::GUIManager::run_loop_() {
    if (!glfwInit()) return;
    GLFWwindow* win = glfwCreateWindow(610, 480,
        ("CAN Sim - node " + std::to_string(6)).c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGui::GetStyle().ScaleAllSizes(1.5);
    ImGui::GetStyle().FontSizeBase = 20.0f;

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //end GUI config
        if (ImGui::Begin("Motor Values Adjustment")) {
            if (ImGui::BeginTabBar("Motors"), ImGuiTabBarFlags_Reorderable) {
                if (ImGui::BeginTabItem("Motor A")) {
                    int v  = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 2);
                    int x  = gui_state_.get<int16_t>(MOTOR_A, 0x2030, 5);
                    if (ImGui::SliderInt("Voltage [2]", &v, 0, 1000))     gui_state_.set<int16_t>(MOTOR_A, 0x2030, 2, v);
                    if (ImGui::SliderInt("MaxMeasured [3]", &x, 0, 1000)) gui_state_.set<int16_t>(MOTOR_A, 0x2030, 5, x);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Motor B")) {
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

        // end GUI config
        ImGui::Render();
        int w, h; glfwGetFramebufferSize(win, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.12f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(win);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(win);
    glfwTerminate();
}
