cmake_minimum_required(VERSION 3.24)
project(orbits)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)

add_executable(orbits main.cpp)

# Link SDL2
target_link_libraries(orbits SDL2::SDL2 SDL2::SDL2main)
