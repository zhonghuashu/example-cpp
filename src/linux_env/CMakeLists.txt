# longopt
add_executable(
    longopt
    longopt.cpp
)

target_link_libraries(
    longopt
    PRIVATE
)

target_include_directories(
    longopt
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# tmpname
add_executable(
    tmpname
    tmpname.cpp
)

target_link_libraries(
    tmpname
    PRIVATE
)

target_include_directories(
    tmpname
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)