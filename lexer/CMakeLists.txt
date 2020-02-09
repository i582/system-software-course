cmake_minimum_required(VERSION 3.15)
project(lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexer main.cpp src/lexer.cpp src/lexer.h)