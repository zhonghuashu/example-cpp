add_library(
    ut-usage
    OBJECT
    SalesItemTest.cpp
    usage_cplus_test.cpp
    usage_func_test.cpp
)

target_link_libraries(
    ut-usage
    PRIVATE
    usage
    GTest::GTest
)
