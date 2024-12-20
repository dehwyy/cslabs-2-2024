cmake_minimum_required(VERSION 3.20)

set(p "interaction")
project(p)

set(${p}_SOURCES
  interaction.cpp
)

set(${p}_HEADERS
  interaction.h
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
