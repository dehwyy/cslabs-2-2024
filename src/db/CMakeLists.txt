cmake_minimum_required(VERSION 3.20)

set(p "db")
project(p)

set(${p}_SOURCES
  db.cpp
  tables/tables.cpp
)

set(${p}_HEADERS
  db.h
  tables/tables.h
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
