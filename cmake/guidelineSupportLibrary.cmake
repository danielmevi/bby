# This cmake module is meant to hold helper functions/macros
# that make maintaining the cmake build system much easier.
# This is especially helpful since bby needs to provide coverage
# for multiple versions of cmake.
#
# Any functions/macros should have a bby_* prefix to avoid problems
if (CMAKE_VERSION VERSION_GREATER 3.10 OR CMAKE_VERSION VERSION_EQUAL 3.10)
    include_guard()
else()
    if (DEFINED guideline_support_library_include_guard)
        return()
    endif()
    set(guideline_support_library_include_guard ON)
endif()

# Necessary for 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

# Use GNUInstallDirs to provide the right locations on all platforms
include(GNUInstallDirs)

function(bby_set_cxx target min_cxx_standard)
    if (DEFINED CMAKE_CXX_STANDARD)
        if (${CMAKE_CXX_STANDARD} VERSION_LESS ${min_cxx_standard})
            message(FATAL_ERROR "BBY: Requires at least CXX standard ${min_cxx_standard}, user provided ${CMAKE_CXX_STANDARD}")
        endif()

        # Set the BBY standard to what the client desires
        set(BBY_CXX_STANDARD "${CMAKE_CXX_STANDARD}")
    else()
        set(BBY_CXX_STANDARD "${min_cxx_standard}" CACHE STRING "Use c++ standard")
    endif()

    set(BBY_CXX_STD "cxx_std_${BBY_CXX_STANDARD}")
    target_compile_features(${target} INTERFACE "${BBY_CXX_STD}")
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(BBY_REQUIRED_FEATURE -fconcepts)
    check_cxx_compiler_flag(${BBY_REQUIRED_FEATURE} has_std_concepts)
    if (has_std_concepts)
      target_compile_options(${target} INTERFACE ${BBY_REQUIRED_FEATURE})
    else()
      message(FATAL_ERROR
        "BBY: Requires CXX standard ${min_cxx_standard} that supports "
        "\"-fconcepts\", user provided ${CMAKE_CXX_STANDARD}")
    endif()

    if (CMAKE_BUILD_TYPE MATCHES ".*Deb.*")
      target_compile_options(${target} INTERFACE -DNDEBUG=1)
    else ()
      target_compile_options(${target} INTERFACE -DNDEBUG=0)
    endif()
endfunction()

# Adding the bby.natvis files improves the debugging experience for users of this library.
function(bby_add_native_visualizer_support)
    if (CMAKE_VERSION VERSION_GREATER 3.7.8)
        if (MSVC_IDE)
            option(BBY_VS_ADD_NATIVE_VISUALIZERS "Configure project to use Visual Studio native visualizers" TRUE)
        else()
            set(BBY_VS_ADD_NATIVE_VISUALIZERS FALSE CACHE INTERNAL "Native visualizers are Visual Studio extension" FORCE)
        endif()

        # add natvis file to the library so it will automatically be loaded into Visual Studio
        if(BBY_VS_ADD_NATIVE_VISUALIZERS)
            target_sources(BBY INTERFACE $<BUILD_INTERFACE:${BBY_SOURCE_DIR}/BBY.natvis>)
        endif()
    endif()
endfunction()

function(bby_install_logic)
    install(TARGETS BBY EXPORT Community.BBYConfig)
    install(
        DIRECTORY include/bby
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    # Make library importable by other projects
    install(EXPORT Community.BBYConfig NAMESPACE Community.BBY:: DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/Community.BBY)
    export(TARGETS BBY NAMESPACE Community.BBY:: FILE Community.BBYConfig.cmake)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Community.BBYConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/Community.BBY)
endfunction()

# Add find_package() versioning support. The version for
# generated Community.bbyConfigVersion.cmake will be used from
# last project() command. The version's compatibility is set between all
# minor versions (as it was in prev. bby releases).
function(bby_create_packaging_file)
    if(${CMAKE_VERSION} VERSION_LESS "3.14.0")
        write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/Community.BBYConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
        )
    else()
        write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/Community.BBYConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
        )
    endif()
endfunction()
