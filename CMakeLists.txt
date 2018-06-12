cmake_minimum_required(VERSION 3.4)
project(Mian-Chowla)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories("${PROJECT_SOURCE_DIR}/Sequences")

# Add the subdirectories.
add_subdirectory(Sequences)
add_subdirectory(Apps)
