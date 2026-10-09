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

if (NOT TARGET hello_imgui)
    message(STATUS "Fetching hello_imgui")
    include(FetchContent)
    FetchContent_Declare(hello_imgui GIT_REPOSITORY https://github.com/pthom/hello_imgui.git GIT_TAG master EXCLUDE_FROM_ALL)
    FetchContent_MakeAvailable(hello_imgui)
endif()

hello_imgui_add_app(can_simulator
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