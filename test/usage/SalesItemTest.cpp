/**
 * @file SalesItemTest.cpp
 * @brief Test code for SalesItem class.
 * @author Shu, Zhong Hua
 * @date 2022-08-15
 */

#include "gtest/gtest.h"
#include "SalesItem.h"
#include <iostream>

namespace usage
{
class SalesItemTest : public testing::Test
{
protected:
    SalesItemTest()
    {
        // You can do set-up work for each test here.
    }

    ~SalesItemTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite.
    // SalesItem m_salesItem;
};

TEST_F(SalesItemTest, avgPrice)
{
    const SalesItem item1("book 1", 1, 20);
    const SalesItem item2("book 2", 1, 40);
    const SalesItem sum = usage::add(item1, item2);
    usage::print(std::cout, sum);

    EXPECT_EQ(30, sum.avgPrice());
}

TEST_F(SalesItemTest, compareIsbn)
{
    const SalesItem item1("book 1", 1, 20);
    const SalesItem item2("book 2", 1, 40);

    EXPECT_EQ(true, usage::compareIsbn(item1, item2));
}

}