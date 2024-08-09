add_executable(
    nanosleep
    nanosleep.cpp
)

target_link_libraries(
    nanosleep
    PRIVATE
)

target_include_directories(
    nanosleep
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    usleep
    usleep.cpp
)

target_link_libraries(
    usleep
    PRIVATE
)

target_include_directories(
    usleep
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    mssleep
    mssleep.cpp
)

add_executable(
    timestamp
    timestamp.cpp
)
