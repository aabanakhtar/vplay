cmake_minimum_required(VERSION 3.22.1)
project(pbr-renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCs
        src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCs})

