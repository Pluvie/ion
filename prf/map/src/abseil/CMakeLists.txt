cmake_minimum_required(VERSION 3.16)

project(ion)

# Abseil requires C++14
set(CMAKE_CXX_STANDARD 14)

# Process Abseil's CMake build system
add_subdirectory(repo)

add_executable(abseil abseil.cpp)

# Declare dependency on the absl::strings library
target_link_libraries(abseil absl::flat_hash_map)
