cmake_minimum_required(VERSION 3.30.5)
project(PDS_AntColonyOptimizationAlgorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(PDS_AntColonyOptimizationAlgorithm main.cpp
        src/Graph.cpp
        src/Graph.h
        src/ant.cpp
        src/ant.h
        src/solvers/ACO.cpp
        src/solvers/ACO.h
        src/solvers/ACO_Serial.cpp
        src/solvers/ACO_Serial.h
        src/solvers/ACO_Parallel.cpp
        src/solvers/ACO_Parallel.h
        src/timer.h
        src/output/OutputWriter.h
        src/output/OutputWriter.cpp
)

# Voor MinGW forceer OpenMP
if(MINGW)
    target_compile_options(PDS_AntColonyOptimizationAlgorithm PUBLIC -fopenmp)
    target_link_options(PDS_AntColonyOptimizationAlgorithm PUBLIC -fopenmp)
else()
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(PDS_AntColonyOptimizationAlgorithm PUBLIC OpenMP::OpenMP_CXX)
    endif()
endif()

