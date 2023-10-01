/**
 * @file usage_cplus_test.cpp
 * @brief usage_cplus test class.
 * @author Shu, Zhong Hua
 * @date 2022-08-23
 */

#include "gtest/gtest.h"
#include "usage_cplus.h"

TEST(usage_cplus_test, usage)
{
    EXPECT_EQ(true, usage::useMain());
}