add_executable(
    perf_main
    perf_main.cpp
)

target_link_libraries(
    perf_main
    PRIVATE
)

target_include_directories(
    perf_main
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
