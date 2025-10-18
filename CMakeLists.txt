cmake_minimum_required(VERSION 3.22.1)
project(vedit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

set(SRCs
    src/main.cpp
    src/window.cpp
)

add_executable(${PROJECT_NAME} ${SRCs})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${LIBAV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PkgConfig::LIBAV
    SDL2::SDL2
)