file(GLOB SOURCES "*.cpp")

add_library(
    math_func
    SHARED
    ${SOURCES}
)

target_include_directories(
    math_func
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS math_func DESTINATION lib)