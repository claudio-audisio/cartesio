cmake_minimum_required(VERSION 4.0)
project(cartesio)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(RAYLIB_INCLUDE_DIR "/home/claudio/Projects/raylib/src")
set(RAYLIB_LIB_DIR "/home/claudio/Projects/raylib/src")

include_directories(${RAYLIB_INCLUDE_DIR})

add_executable(cartesio cartesio.cpp)

target_link_libraries(cartesio PRIVATE ${RAYLIB_LIB_DIR}/libraylib.a -lm -lpthread -ldl -lrt -lX11)
