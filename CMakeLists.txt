cmake_minimum_required(VERSION 4.0)
project(cartesio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto=auto")

set(SRC_FOLDERS
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

add_subdirectory(../claLib ${CMAKE_BINARY_DIR}/claLib)
add_library(cartesioLib ${ALL_SOURCES})

target_include_directories(cartesioLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cartesio cartesio.cpp)

target_link_libraries(cartesio PRIVATE claLib)
target_link_libraries(cartesio PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
target_link_libraries(cartesio PRIVATE cartesioLib)

############ TESTS ###################################################################################################################################################
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

set(TEST_NAMES
        functionTest
)

foreach(test ${TEST_NAMES})
    add_executable(${test} "test/${test}.cpp")
    target_link_libraries(${test} GTest::gtest_main cartesioLib)
    gtest_discover_tests(${test})
endforeach()
