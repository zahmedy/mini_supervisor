cmake_minimum_required(VERSION 3.15)
project(mini_supervisor VERSION 1.0 LANGUAGES CXX)

# Require C++17 or higher
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify header search paths
include_directories(include)

# Gather source files and define the tarett executable
add_executable(mini_supervisor
    src/main.cpp
    src/Process.cpp
)
