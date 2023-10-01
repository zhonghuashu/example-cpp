#include <cstdio>
#include <gtest/gtest.h>

static int add(const int a, const int b)
{
    return a + b;
}

TEST(MyTest, AddTest)
{
    EXPECT_EQ(add(1, 2), 3);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}