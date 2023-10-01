# fileio
add_executable(
    fileio
    fileio.cpp
)

target_link_libraries(
    fileio
    PRIVATE
)

target_include_directories(
    fileio
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# stdio
add_executable(
    stdio
    stdio.cpp
)

target_link_libraries(
    stdio
    PRIVATE
)

target_include_directories(
    stdio
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# stdio
add_executable(
    printdir
    printdir.cpp
)

target_link_libraries(
    printdir
    PRIVATE
)

target_include_directories(
    printdir
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# mmap
add_executable(
    mmap
    mmap.cpp
)

target_link_libraries(
    mmap
    PRIVATE
)

target_include_directories(
    mmap
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)