# Based on the example at: https://cmake.org/examples/

cmake_minimum_required(VERSION 3.4)
project(Mian-Chowla)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(/usr/local/include)
include_directories(/usr/local/Cellar/gcc@7/7.3.0/include/c++/7.3.0)
link_directories(/usr/local/lib)
link_directories(/usr/local/Cellar/gcc@7/7.3.0/lib)

# Add the subdirectories.
add_subdirectory(Sequences)
add_subdirectory(Apps)
