cmake_minimum_required(VERSION 4.0)
project(cartesio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto=auto")

set(SRC_FOLDERS
        "."
        "board"
        "muparser"
)

foreach(dir ${SRC_FOLDERS})
    file(GLOB_RECURSE FOLDER_FILES
            CONFIGURE_DEPENDS
            "${dir}/*.cpp"
            "${dir}/*.h"
    )
    list(APPEND ALL_SOURCES ${FOLDER_FILES})
endforeach()

add_library(cartesioLib ${ALL_SOURCES})

target_include_directories(cartesioLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cartesio cartesio.cpp)

target_link_libraries(cartesio PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
target_link_libraries(cartesio PRIVATE cartesioLib)
