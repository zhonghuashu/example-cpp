/**
 * @file thread_sample_test.cpp
 * @brief Thread sample test class.
 * @author Shu, Zhong Hua
 * @date 2022-08-24
 */

#include "gtest/gtest.h"
#include "thread_func.h"

TEST(thread_sample_test, main)
{
    EXPECT_EQ(true, ::thread_main());
}