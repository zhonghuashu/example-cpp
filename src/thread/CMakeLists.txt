set(SOURCES_LIB
    thread_func.c
)

set(SOURCES_BIN
    thread_main.c
)

add_library(
    thread_func
    SHARED
    ${SOURCES_LIB}
)

target_link_libraries(
    thread_func
    PRIVATE
    pthread
)

target_include_directories(
    thread_func
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    thread_main
    ${SOURCES_BIN}
)

target_link_libraries(
    thread_main
    PRIVATE
    thread_func
)

# threadsimple
add_executable(
    thread_simple
    thread_simple.cpp
)

target_link_libraries(
    thread_simple
    PRIVATE
    pthread
)

target_include_directories(
    thread_simple
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS thread_func DESTINATION lib)
install(TARGETS thread_simple DESTINATION bin)
install(TARGETS thread_main DESTINATION bin)