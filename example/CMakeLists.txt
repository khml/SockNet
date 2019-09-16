cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME sockNetExample)
set(SockNetIncludePath /usr/local/include)
set(SockNetLibPath /usr/local/lib/SockNet)

project(${PROJECT_NAME} VERSION 1.0.0 DESCRIPTION "A SockNet Example Program")

file(GLOB SOURCES example.cpp)
include_directories(BEFORE ${SockNetIncludePath})

find_library (
        SockNet
        NAMES SockNet libSockNet
        HINTS ${SockNetLibPath}
)

set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SockNet})
