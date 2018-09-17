cmake_minimum_required(VERSION 3.10)
enable_testing()
option(ENABLE_TESTS "Enable testing" ON)
# use clang-tidy if it's available
find_program(CLANG_TIDY clang-tidy)

project(noteconverter LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_library(project_warnings INTERFACE)

if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4)
else()
    target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(third_party)
add_subdirectory(tests)


if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()
add_subdirectory(src)
