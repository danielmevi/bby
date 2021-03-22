cmake_minimum_required(VERSION 2.8.12)
project(IndexRanges)

add_definitions("-std=c++14")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

find_package(GTest REQUIRED)

add_executable(indexranges unittest.cc)
target_link_libraries(indexranges ${CONAN_LIBS})
