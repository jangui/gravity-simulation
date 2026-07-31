cmake_minimum_required(VERSION 3.24)
project(gravity-simulation)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)

add_executable(
        gravity-simulation
        main.cpp
        Application.cpp
        platform/SdlContext.cpp
        platform/Window.cpp
        render/Renderer.cpp
)

# Link SDL2
target_link_libraries(gravity-simulation SDL2::SDL2 SDL2::SDL2main)
