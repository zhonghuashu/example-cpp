# tmpname
add_executable(
    system
    system.cpp
)

target_link_libraries(
    system
    PRIVATE
)

target_include_directories(
    system
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# fork
add_executable(
    fork
    fork.cpp
)

target_link_libraries(
    fork
    PRIVATE
)

target_include_directories(
    fork
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# signal
add_executable(
    signal
    signal.cpp
)

target_link_libraries(
    signal
    PRIVATE
)

target_include_directories(
    signal
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# alarm
add_executable(
    alarm
    alarm.cpp
)

target_link_libraries(
    alarm
    PRIVATE
)

target_include_directories(
    alarm
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)