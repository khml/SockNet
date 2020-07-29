cmake_minimum_required(VERSION 3.10)

project(sockNetExample)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} socknet)
