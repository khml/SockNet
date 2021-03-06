cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME socknet)
project(${PROJECT_NAME} VERSION 0.3.0 DESCRIPTION "C++ Socket Wrapper")

set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall")

include_directories(include)

file(GLOB SOURCES src/socknet/*.cpp src/socknet/core/*.cpp)
file(GLOB HEADERS include/socknet/*.hpp include/socknet/core/*.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION a030)
target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})