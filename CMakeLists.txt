cmake_minimum_required(VERSION 3.19)
project(PointsDistance)

set(CMAKE_CXX_STANDARD 20)

add_executable(PointsDistance src/main.cc include/DistanceFunctions.hpp src/DistanceFunctions.cc)