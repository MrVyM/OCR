cmake_minimum_required(VERSION 3.00)

# Set the project name
project(SudokuSolver VERSION 0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set the CXXFLAGS
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

# Get all src files (cpp)
file(GLOB_RECURSE SRC src/*.c)

# Add include dir
include_directories(include)

# Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ouput Executable
add_executable(final.out ${SRC})
