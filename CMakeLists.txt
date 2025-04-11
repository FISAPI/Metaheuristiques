cmake_minimum_required(VERSION 3.30)
project(scp_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(scp_solver
        src/main.cpp
        src/retrieving_data.cpp
        src/greedy_algorithm.cpp
        src/dual_fitting_algorithm.cpp
        src/metaheuristic.cpp
        src/genetic_algorithm.cpp
)
