cmake_minimum_required(VERSION 3.1.3...3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(guidelineSupportLibrary)

project(CCXT
    VERSION 1.0.0
    LANGUAGES CXX
)

include(PreventInSourceBuilds)

# Creates a library CCXT which is an interface (header files only)
add_library(CCXT INTERFACE)

# Determine whether this is a standalone project or included by other projects
set(CCXT_STANDALONE_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CCXT_STANDALONE_PROJECT ON)
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

include(conan.cmake)

conan_add_remote(
  NAME bincrafters
  URL  https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
  REQUIRES gtest/1.10.0
           benchmark/1.5.2
           libcurl/7.73.0
           fmt/7.1.0
           ms-gsl/3.1.0
           rapidjson/1.1.0
  OPTIONS
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD missing
  BUILD_TYPE "Release")

# NOTE: If you want to use CCXT prefer to link against CCXT using this alias target
# EX:
#   target_link_libraries(foobar PRIVATE Corpsoft.CCXT::CCXT)
#
# Add Corpsoft.CCXT::CCXT alias for CCXT so that dependents can be agnostic about
# whether CCXT was added via `add_subdirectory` or `find_package`
add_library(Corpsoft.CCXT::CCXT ALIAS CCXT)

### Project options
option(CCXT_INSTALL "Generate and install CCXT target" ${CCXT_STANDALONE_PROJECT})
option(CCXT_TEST "Build and perform CCXT tests" ${CCXT_STANDALONE_PROJECT})

set(ccxt_min_cxx_standard "20")
ccxt_set_cxx(CCXT ${ccxt_min_cxx_standard})

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)

target_link_libraries(CCXT INTERFACE
                                curl # Workaround since conan libcurl is not working
                                #CONAN_PKG::libcurl
                                CONAN_PKG::ms-gsl
                                CONAN_PKG::fmt
                                CONAN_PKG::rapidjson)

if(CCXT_STANDALONE_PROJECT)
    target_include_directories(CCXT INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
else()
    target_include_directories(CCXT SYSTEM INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
endif()

# Add natvis file
ccxt_add_native_visualizer_support()

# Add packaging support
ccxt_create_packaging_file()

if (CCXT_INSTALL)
    # Setup install/export logic
    ccxt_install_logic()
endif()

if (CCXT_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
