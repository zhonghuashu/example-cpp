add_library(
    ut-thread
    OBJECT
    thread_func_test.cpp
)

target_link_libraries(
    ut-thread
    PRIVATE
    thread_func
    GTest::GTest
)
