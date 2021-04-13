#
# Test CMake
#

set(CLANG_WARNINGS
    -Wall
    -Wextra # reasonable and standard
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
                       # catch hard to track down memory errors
    -Wold-style-cast # warn for c-style casts
    -Wcast-align # warn for potential performance problem casts
    -Wunused # warn on anything being unused
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wformat=2 # warn on security issues around functions that format output (ie printf)
)
set(GCC_WARNINGS
    ${CLANG_WARNINGS}
    -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    -Wuseless-cast # warn if you perform a cast to the same type
    -Wzero-as-null-pointer-constant
    -Wvector-operation-performance
    -Wsized-deallocation
    -Wdouble-promotion
    -Wtrampolines
    -Wno-dangling-else
    -Wno-unused-local-typedefs
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(PEDANTIC_COMPILE_FLAGS ${GCC_WARNINGS})
  set(WERROR_FLAG -Werror)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS ${CLANG_WARNINGS})
  set(WERROR_FLAG -Werror)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy
  -checks=-*,readability-*,clang-analizer-*,cppcoreguidelnes-*,performance-*,modernize-*,-modernize-use-trailing-return-type)
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

set(TEST_MAIN_SRC test-main.cpp)
add_library(test-main STATIC ${TEST_MAIN_SRC})
target_link_libraries(test-main PUBLIC
                                CONAN_PKG::gtest
                                CONAN_PKG::benchmark
                                CONAN_PKG::ms-gsl
                                CONAN_PKG::fmt)

bby_set_cxx(test-main ${bby_min_cxx_standard})

# Adds a test.
# Usage: add_bby_test(name srcs...)
function(add_bby_test name)
  add_executable(${name} ${name}.cpp ${ARGN})
  target_link_libraries(${name} test-main)

  # Define if certain C++ features can be used.
  target_compile_options(${name} PRIVATE ${PEDANTIC_COMPILE_FLAGS})
  if (BBY_WERROR)
    target_compile_options(${name} PRIVATE ${WERROR_FLAG})
  endif ()

  if (${name} MATCHES "unit-benchmark")
    target_include_directories(${name} BEFORE PUBLIC stubs)
  endif()
  target_include_directories(${name} PUBLIC ../include)

  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_bby_test(state_machine-test)
add_bby_test(scope_guard-test)
add_bby_test(one_thread_scheduler-test)
add_bby_test(numeric-test)
add_bby_test(metaprogram-test)
add_bby_test(index_range-test)
add_bby_test(date_handler-test)
add_bby_test(byte_copy-test)
add_bby_test(buffer_cast-test)
add_bby_test(lru_cache-test)
