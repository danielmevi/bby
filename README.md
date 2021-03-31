[![Build Status](https://travis-ci.com/danielmevi/bby.svg?branch=master)](https://travis-ci.com/danielmevi/bby)

# BBY C++ library utility
Welcome to the Baby C++ library utilities

The entire implementation is provided inline in the headers under the [bby](include/bby/bby.h). The implementation assumes a platform that implements C++20 support. Therefore the library can be manually added through the main header or by CMake.

## Third-party libraries

* https://github.com/conan-io/cmake-conan.git
* https://github.com/google/googletest
* https://github.com/microsoft/GSL.git
* https://github.com/fmtlib/fmt.git

## Toolset

* C++20
* Conan
* CMake
* Ctest
* GCC
* Clang
* Git

## Utilities

### Semantic State Machine
TODO: Add description

### Scope Guards
TODO: Add description

### One Thread Scheduler
TODO: Add description

### Byte Copies
TODO: Add description

### Index Range
TODO: Add description

### Date Handler
TODO: Add description

### Buffer Cast
TODO: Add description

### LRU Cache
TODO: Add description

# Quick Start
## Supported platforms
The test suite that exercises C++ BBY has been built and passes successfully 
on the following platforms:

* Ubuntu 20.04 using GCC <TODO>

## Building the test
1. mkdir build

2. cd build

3. cmake <bby_repository>

4. make

5. ctest

## Integration
### Manual
Add `#include include/bby` into te client source code and `-I<path to bby repository>` to gain access to the complete library

### CMake
Place the `bby` project within the customer project and use the following
commands to include `bby`:
- `add_subdirectory(bby_cpp)`
- `target_link_libraries(bby_client PRIVATE Community.BBY::BBY)`

Directory structure for a client project:
```
- client/
--- CMakeList.txt
--- client_code.cpp
--- bby_cpp/
------- CMakeList.txt
------- Rest of bby library
```

NOTE: `find_project` is not enabled yet

#### Example for project to include and link `bby` with CMake
```
cmake_minimum_required(VERSION 3.15)

project(BBY_CLIENT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_subdirectory(bby_cpp)

set(SOURCE_FILES main.cpp)
add_executable(bby_client ${SOURCE_FILES})
target_link_libraries(bby_client PRIVATE Community.BBY::BBY)
```

Client code can reference from any of the available unit test [test](./test)
