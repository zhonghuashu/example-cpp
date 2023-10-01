add_library(
    ut-math-func
    OBJECT
    math_func_test.cpp
)

target_link_libraries(
    ut-math-func
    PRIVATE
    math_func
    GTest::GTest
)
