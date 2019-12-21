cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME SockNet)
project(${PROJECT_NAME} VERSION 0.0.1 DESCRIPTION "C++ Socket Wrapper")

set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall")

include_directories(headers)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS headers/*.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
target_include_directories(${PROJECT_NAME} PUBLIC headers)
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})