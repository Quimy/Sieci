cmake_minimum_required(VERSION 3.5.1)
project(httpServer)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

find_package (Threads)

add_executable(httpServer ${SOURCES})

target_link_libraries (httpServer ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET httpServer PROPERTY CXX_STANDARD 14)
set_property(TARGET httpServer PROPERTY CXX_STANDARD_REQUIRED ON)