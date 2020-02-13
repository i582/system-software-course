cmake_minimum_required(VERSION 3.15)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/lexer)

add_executable(compiler
        src/lexer/lexer.cpp
        src/lexer/lexer.h
        main.cpp
        src/syntaxer/syntaxer.cpp
        src/syntaxer/syntaxer.h
        src/syntaxer/various_implementation/variable_declaration.cpp
        src/syntaxer/various_implementation/variable_declaration.h
        src/syntaxer/various_implementation/variable.cpp
        src/syntaxer/various_implementation/variable.h
        src/lexer/block/block.cpp src/lexer/block/block.h
        src/lexer/block/simple_block.cpp
        src/lexer/block/simple_block.h
        src/lexer/block/extended_block.cpp
        src/lexer/block/extended_block.h
        src/lexer/block/blocks/for/for_implementation.cpp
        src/lexer/block/blocks/for/for_implementation.h src/lexer/token/token.cpp src/lexer/token/token.h)
