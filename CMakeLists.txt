cmake_minimum_required(VERSION 3.20)

project(Fractions) # <- project name

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
set(HEADERS
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/app.h # <- add project .h files
)


add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)

add_subdirectory(src/fraction)
target_link_libraries(${CMAKE_PROJECT_NAME} fraction)
