cmake_minimum_required(VERSION 3.28)
project(can_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LELY REQUIRED
        liblely-coapp
        liblely-co
        liblely-io2
        liblely-ev
        liblely-can
        liblely-util
)

add_executable(can_simulator
        src/main.cpp
        src/can/motor/SimMotorController.cpp
        src/can/SimManager.cpp
        src/gui/GUIManager.cpp
        src/gui/GUIStateManager.cpp
)

target_include_directories(can_simulator
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PRIVATE ${LELY_INCLUDE_DIRS}
)

target_link_libraries(can_simulator
        PRIVATE ${LELY_LIBRARIES}
)

target_compile_options(can_simulator
        PRIVATE ${LELY_CFLAGS_OTHER}
)

option(CAN_SIM_GUI "Build with Dear ImGui front-end" ON)

if(CAN_SIM_GUI)
    include(FetchContent)
    FetchContent_Declare(imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG        v1.92.9)
    FetchContent_MakeAvailable(imgui)

    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)

    add_library(imgui_lib STATIC
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
    target_include_directories(imgui_lib PUBLIC
            ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
    target_link_libraries(imgui_lib PUBLIC glfw OpenGL::GL)
endif()

target_link_libraries(can_simulator PRIVATE ${LELY_LIBRARIES} imgui_lib)
target_compile_definitions(can_simulator PRIVATE CAN_SIM_GUI=1)
