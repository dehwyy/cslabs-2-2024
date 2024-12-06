cmake_minimum_required(VERSION 3.20)

set(p "mymath")
project(p)

set(${p}_SOURCES
  mymath.cpp
)

set(${p}_HEADERS
    mymath.h
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
