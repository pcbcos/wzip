cmake_minimum_required(VERSION 3.23)
project(wzip)

set(CMAKE_CXX_STANDARD 20)

add_executable(wzip wzip.cpp datatypes.cpp HuffmanZip.cpp)
add_executable(unwzip unwzip.cpp datatypes.cpp HuffmanUnZip.cpp)