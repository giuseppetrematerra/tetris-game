cmake_minimum_required(VERSION 3.17)
project(Tetris C)

set(CMAKE_C_STANDARD 99)
file(GLOB SOURCES *.c *.h)

add_executable(Tetris ${SOURCES})