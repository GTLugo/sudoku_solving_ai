cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(sudoku_ai)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/$<CONFIG>/${CMAKE_SYSTEM_NAME}")

set(SOURCES
    src/main.cpp
    src/sudoku/agent.cpp
    src/sudoku/sudoku.cpp)

add_executable(sudoku_ai ${SOURCES})

target_include_directories(sudoku_ai PUBLIC src)
