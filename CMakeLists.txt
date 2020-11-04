cmake_minimum_required(VERSION 3.18)

project(GSF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O2 -Wall")
add_executable(${PROJECT_NAME} main.cpp)