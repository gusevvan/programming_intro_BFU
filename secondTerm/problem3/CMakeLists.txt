cmake_minimum_required(VERSION 3.24)
project(problem3)

set(CMAKE_CXX_STANDARD 17)

add_executable(problem3 main.cpp)

target_link_libraries(problem3 sfml-graphics
        sfml-window
        sfml-system)
