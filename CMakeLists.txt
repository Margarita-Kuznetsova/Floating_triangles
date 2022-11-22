cmake_minimum_required(VERSION 3.10)
project(Triangles)

set(CMAKE_C_COMPILER   "/usr/bin/clang")
set(CMAKE_C_FLAGS      "-Wall -std=c99")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS    "-Wall -std=c++2a")

find_package(SFML 2 COMPONENTS network graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_executable(output main.c logic.c picture.cpp)
target_link_libraries(
    output
    sfml-graphics 
    sfml-network
    sfml-audio 
  )