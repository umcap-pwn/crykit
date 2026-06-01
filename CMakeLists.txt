cmake_minimum_required(VERSION 3.20)
project(ciphers CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ciphers)
add_subdirectory(cli)
add_subdirectory(tests)
