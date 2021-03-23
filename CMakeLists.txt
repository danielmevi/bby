cmake_minimum_required(VERSION 3.1.3...3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(guidelineSupportLibrary)

project(BBY
    VERSION 0.1.0
    LANGUAGES CXX
)

include(PreventInSourceBuilds)

# Creates a library BBY which is an interface (header files only)
add_library(BBY INTERFACE)

# Determine whether this is a standalone project or included by other projects
set(BBY_STANDALONE_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(BBY_STANDALONE_PROJECT ON)
endif()

# Set a default build type if none was specified
if (CCXT_STANDALONE_PROJECT AND NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

include(cmake/conan.cmake)

conan_add_remote(
  NAME bincrafters
  URL  https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
  REQUIRES gtest/1.10.0
           benchmark/1.5.2
           fmt/7.1.0
           ms-gsl/3.1.0
  OPTIONS
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD missing)

# NOTE: If you want to use BBY prefer to link against BBY using this alias target
# EX:
#   target_link_libraries(foobar PRIVATE Community.BBY::BBY)
#
# Add Community.BBY::BBY alias for BBY so that dependents can be agnostic about
# whether BBY was added via `add_subdirectory` or `find_package`
add_library(Community.BBY::BBY ALIAS BBY)


### Project options
option(BBY_INSTALL "Generate and install BBY target" ${BBY_STANDALONE_PROJECT})
option(BBY_TEST "Build and perform BBY tests" ${BBY_STANDALONE_PROJECT})

set(bby_min_cxx_standard "20")
bby_set_cxx(BBY ${bby_min_cxx_standard})

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)

target_link_libraries(BBY INTERFACE
                                CONAN_PKG::ms-gsl
                                CONAN_PKG::fmt)

if(BBY_STANDALONE_PROJECT)
    target_include_directories(BBY INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
else()
    target_include_directories(BBY SYSTEM INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
endif()

# Add natvis file
bby_add_native_visualizer_support()

# Add packaging support
bby_create_packaging_file()

if (BBY_INSTALL)
    # Setup install/export logic
    bby_install_logic()
endif()

if (BBY_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
