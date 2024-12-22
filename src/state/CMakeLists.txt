cmake_minimum_required(VERSION 3.20)

set(p "state")
project(p)

set(${p}_SOURCES
  state.cpp
)

set(${p}_HEADERS
  state.hpp
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
