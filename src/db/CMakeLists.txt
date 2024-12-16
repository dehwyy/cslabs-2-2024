cmake_minimum_required(VERSION 3.20)

set(p "db")
project(p)

set(${p}_SOURCES
  db.cpp
  tables/tables.cpp
  tables/table_name.cpp
  serde/serde.cpp
  entity/entity.cpp
)

set(${p}_HEADERS
  db.h
  tables/tables.h
  tables/table_name.h
  serde/serde.h
  entity/entity.h
)

add_library(${p} STATIC ${${p}_SOURCES} ${${p}_HEADERS})

target_compile_options(${p} PRIVATE -Wall -Wextra -Werror -Wpedantic)
