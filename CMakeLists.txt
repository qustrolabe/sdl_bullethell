cmake_minimum_required(VERSION 3.9)
project(sdl_bullethell)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} src)

file(COPY textures DESTINATION .)

add_executable(sdl_bullethell src/main.cpp)
target_link_libraries(sdl_bullethell SDL2main SDL2)
