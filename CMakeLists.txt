cmake_minimum_required(VERSION 3.9)
project(sdlteste)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(COPY textures DESTINATION .)

add_executable(sdlteste main.cpp)
target_link_libraries(sdlteste SDL2main SDL2)
