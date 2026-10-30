cmake_minimum_required(VERSION 3.21)
project(can_simulator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(can_simulator
        src/main.cpp
        include/can/generic/SimCanDevice.h
        src/can/CanIo.cpp
        src/can/sensors/ExampleSensor.cpp
        src/can/generic/EBPSimDevice.cpp
        src/can/devices/ExampleDevice.cpp
        src/can/SimManager.cpp
        include/can/generic/EBPStructs.h
)
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
CPMAddPackage(
        NAME sockcanpp
        GIT_REPOSITORY https://github.com/SimonCahill/libsockcanpp.git
        GIT_TAG master
)

target_link_libraries(
        can_simulator PUBLIC
        sockcanpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
