cmake_minimum_required(VERSION 3.1)

project(thrift_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    add_definitions(-DNOMINMAX)
endif()

add_subdirectory(libthrift)
add_subdirectory(thrifts)

add_subdirectory(client)
add_subdirectory(server)
