cmake_minimum_required(VERSION 3.21)
project(can_simulator CXX)

set(CMAKE_CXX_STANDARD 14)
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
)

target_include_directories(can_simulator
        PRIVATE ${LELY_INCLUDE_DIRS}
)

target_link_libraries(can_simulator
        PRIVATE ${LELY_LIBRARIES}
)

target_compile_options(can_simulator
        PRIVATE ${LELY_CFLAGS_OTHER}
)
