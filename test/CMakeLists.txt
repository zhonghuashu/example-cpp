find_package(GTest 1.12.1)
include_directories(${GTEST_INCLUDE_DIR})
message(STATUS "GTest found: ${GTEST_FOUND} ${GTEST_INCLUDE_DIR}")

if (NOT ${GTEST_FOUND})
    # Fetch googletest.
    include(${PROJECT_SOURCE_DIR}/cmake/googletest.cmake)
    fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
    )
    return()
endif()

add_subdirectory(usage)
add_subdirectory(math_func)
add_subdirectory(thread)

add_executable(
    ut-main
    unittest_main.cpp
    $<TARGET_OBJECTS:ut-math-func>
    $<TARGET_OBJECTS:ut-thread>
    $<TARGET_OBJECTS:ut-usage>
)

target_link_libraries(
    ut-main
    PRIVATE
    GTest::GTest
    pthread
    math_func
    thread_func
    usage
)

target_include_directories(
    ut-main
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test
    ${PROJECT_BINARY_DIR}/src
)

add_test(
    NAME ut-main
    COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/ut-main
)

install(TARGETS ut-main DESTINATION bin)