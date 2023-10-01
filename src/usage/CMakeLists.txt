set(SOURCES_LIB
    Quote.cpp
    SalesItem.cpp
    usage_cplus.cpp
    usage_func.c
)

add_library(
    usage
    SHARED
    ${SOURCES_LIB}
)

target_link_libraries(
    usage
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    usage
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}/src
    ${FMT_INCLUDES}
)

add_executable(
    hello_c
    hello_c.c
)
target_link_libraries(
    hello_c
    PRIVATE
    usage
)

target_include_directories(
    hello_c
    PUBLIC
    ${PROJECT_BINARY_DIR}/src
)

add_executable(
    hello_cpp
    hello_cpp.cpp
)

target_link_libraries(
    hello_cpp
    PRIVATE
    usage
)

target_include_directories(
    hello_cpp
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/src
)

install(TARGETS usage DESTINATION lib)
install(TARGETS hello_c DESTINATION bin)
install(TARGETS hello_cpp DESTINATION bin)
install(
    FILES
    ${PROJECT_BINARY_DIR}/src/config.h
    DESTINATION include/${CMAKE_PROJECT_NAME}
)
