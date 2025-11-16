cmake_minimum_required(VERSION 4.0)
project(PDS_AntColonyOptimizationAlgorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(PDS_AntColonyOptimizationAlgorithm main.cpp
        src/Graph.cpp
        src/Graph.h
        src/ant.cpp
        src/ant.h
        src/ACO.cpp
        src/ACO.h
)
