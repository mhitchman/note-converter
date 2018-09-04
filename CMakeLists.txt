cmake_minimum_required(VERSION 3.10)
enable_testing()
option(ENABLE_TESTS "Enable testing" ON)

project(noteconverter LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(custom_compile_options -Wall -Wextra -Wpedantic)

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(tests)

# use clang-tidy if it's available
find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()
