cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(serializiation)

find_package(Boost REQUIRED COMPONENTS serialization)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE Boost::serialization)

