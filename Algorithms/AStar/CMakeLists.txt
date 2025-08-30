cmake_minimum_required(VERSION 3.16)
project(AStarPathFinding)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/map.cpp
                src/pathfinder.cpp
                )
file(COPY data/map.txt DESTINATION ${CMAKE_BINARY_DIR})



