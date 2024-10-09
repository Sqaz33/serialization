cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(serializiation)

# find_package(Boost REQUIRED COMPONENTS serialization)

file(GLOB_RECURSE SRCS "./src/*.cpp")

add_executable(main ${SRCS})

# target_link_libraries(main PRIVATE Boost::serialization)

