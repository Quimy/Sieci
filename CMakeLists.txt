cmake_minimum_required(VERSION 3.5.1)
project(httpServer)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(httpServer ${SOURCES})

set_property(TARGET httpServer PROPERTY CXX_STANDARD 14)
set_property(TARGET httpServer PROPERTY CXX_STANDARD_REQUIRED ON)