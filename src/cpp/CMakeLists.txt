cmake_minimum_required(VERSION 3.31)
project(Tortilla)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tortilla
        main.cpp
        lexer.cpp
        lexer.h
        error.cpp
        error.h
        AST.cpp
        AST.h
        Parser.h
        parser.cpp
        Common.h
        Debug.h
        Semantic.h
        Semantic.cpp

)