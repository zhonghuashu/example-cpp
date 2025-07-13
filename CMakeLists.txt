cmake_minimum_required(VERSION 3.16)

# Set the project name and version.
project(example-cpp LANGUAGES C CXX)
include(cmake/GetVersionFromGitTag.cmake)

# Detect operating system and host processor.
message(STATUS "Host / target system: ${CMAKE_HOST_SYSTEM_NAME} / ${CMAKE_SYSTEM_NAME}")
message(STATUS "Host / target processor: ${CMAKE_HOST_SYSTEM_PROCESSOR} / ${CMAKE_SYSTEM_PROCESSOR}")

# Check cross compiling on target or native host build.
if(${CMAKE_CROSSCOMPILING})
    message(STATUS "Cross compiling on target")
    set(CMAKE_INSTALL_PREFIX "./install/arm")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_INSTALL_PREFIX} "./rootfs/arm-cyclone5")
else()
    message(STATUS "Cross compiling on host")
    set(CMAKE_INSTALL_PREFIX "./install/x86_64")
    # installed via: apt install libfmt-dev
    # set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_INSTALL_PREFIX} "./rootfs/x86-host" "/root/develop/x86-host-rootfs" "/root/develop/x86-host-extra")
endif()

# Configure header file.
configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_BINARY_DIR}/src/config.h
)

# Set C++ standard veraibles.
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
if (COMPILER_SUPPORTS_CXX20)
    set(CMAKE_CXX_STANDARD 20)
    # should we use our own math functions
    option(USE_STRING_FORMAT "Use string format provided by standard C++ library" ON)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++20 support")
else()
    set(CMAKE_CXX_STANDARD 14)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Place binaries and libraries according to GNU standards.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Set c++ compiler flags.
# -Wno-psabi: disable note: parameter passing for argument of type ‘std::initializer_list<double>’ changed in GCC 7.1
# CMAKE_CXX_FLAGS_DEBUG:STRING=-g
# CMAKE_CXX_FLAGS_RELEASE:STRING=-O3 -DNDEBUG
# --coverage: code coverage
add_compile_options(-fprofile-arcs -ftest-coverage -Wall -Wno-psabi)
add_link_options(--coverage)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enable testing.
enable_testing()

# cpack
include(InstallRequiredSystemLibraries)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Search for 3rd party library path.
find_library(FMT_LIBRARY NAMES fmt)

find_path(FMT_INCLUDES fmt/core.h)
message(STATUS "FMT_LIBRARY: ${FMT_LIBRARY}")
message(STATUS "FMT_INCLUDES: ${FMT_INCLUDES}")
add_subdirectory(src)
if(NOT ${CMAKE_CROSSCOMPILING})
    # Skip GoogleTest in cross-compiler if GCC version less than 5+.
    add_subdirectory(test)
endif()