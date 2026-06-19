cmake_minimum_required(VERSION 3.20)
project(ciphers CXX)

enable_testing()
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ciphers)
add_subdirectory(cli)
add_subdirectory(tests)
add_subdirectory(utils)
