cmake_minimum_required(VERSION 3.16)

project(RoadSim C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOLUTION_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/raylib)
add_compile_definitions(RAYGUI_IMPLEMENTATION)

file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
)

add_executable(RoadSim ${PROJECT_SOURCES})

target_include_directories(RoadSim PRIVATE src)

target_link_libraries(RoadSim PRIVATE raylib)

message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS target")

    target_link_libraries(RoadSim PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreAudio"
        "-framework AudioToolbox"
    )

elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring for Windows target")

    # Static Windows build
    target_link_options(RoadSim PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )

elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring for Linux target")

    target_link_libraries(RoadSim PRIVATE m pthread dl)

endif()
