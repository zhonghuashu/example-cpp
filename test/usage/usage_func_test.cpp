/**
 * @file usage_func_test.cpp
 * @brief usage_func test class.
 * @author Shu, Zhong Hua
 * @date 2022-08-23
 */

#include "gtest/gtest.h"
#include "usage_func.h"

TEST(usage_func_test, usage)
{
    EXPECT_EQ(true, ::usage_cmain());
}