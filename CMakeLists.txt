cmake_minimum_required(VERSION 3.26)
project(Proj3Spotify)

set(CMAKE_CXX_STANDARD 17)

# Include project root directory
include_directories(${PROJECT_SOURCE_DIR})

# Add executable
add_executable(Proj3Spotify
        main.cpp
        backend.h
        algorithms.h)

# Add Windows socket libraries
target_link_libraries(Proj3Spotify wsock32 ws2_32)