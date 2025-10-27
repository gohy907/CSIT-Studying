cmake_minimum_required(VERSION 3.15)
project(task3 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCES
    main.cpp
    complexNumber.cpp
    list.cpp
    error.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
