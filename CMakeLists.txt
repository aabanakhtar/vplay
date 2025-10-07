cmake_minimum_required(VERSION 3.22.1)
project(vedit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# setup ffmpeg (for the pkg_chekc_modules, the first arg is a prefix for all variables i guess)
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWSCALE REQUIRED libswscale)

set(SRCs
        src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCs})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    ${AVFORMAT_CFLAGS_OTHER}
    ${AVCODEC_CFLAGS_OTHER}
    ${AVUTIL_CFLAGS_OTHER}
    ${SWSCALE_CFLAGS_OTHER}
)

