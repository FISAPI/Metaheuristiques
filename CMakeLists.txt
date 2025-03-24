cmake_minimum_required(VERSION 3.30)
project(scp_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(scp_solver
        src/main.cpp
        src/retrieving_data.cpp
)
