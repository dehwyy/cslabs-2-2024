cmake_minimum_required(VERSION 3.20)

set(p "planets")
project(p)

set(${p}_SOURCES
  planets.cpp
)

set(${p}_HEADERS
  planets.h
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
