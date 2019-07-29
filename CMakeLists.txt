cmake_minimum_required(VERSION 3.13)
project(SockNet)

set(CMAKE_CXX_STANDARD 11)

add_executable(SockNet src/main.cpp src/Client.cpp src/Connector.cpp src/Server.cpp)