// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @file sample1_test.cpp
 * @brief Sample test class.
 * @author Shu, Zhong Hua
 * @date 2022-08-23
 */
#include <climits>
#include "gtest/gtest.h"
#include "math_func.h"

TEST(FactorialTest, Negative)
{
    // This test is named "Negative", and belongs to the "FactorialTest"
    // test case.
    EXPECT_EQ(1, math_func::factorial(-5));
    EXPECT_EQ(1, math_func::factorial(-1));
    EXPECT_GT(math_func::factorial(-10), 0);
}

TEST(FactorialTest, Zero)
{
    EXPECT_EQ(1, math_func::factorial(0));
}

TEST(FactorialTest, Positive)
{
    EXPECT_EQ(1, math_func::factorial(1));
    EXPECT_EQ(2, math_func::factorial(2));
    EXPECT_EQ(6, math_func::factorial(3));
    EXPECT_EQ(40320, math_func::factorial(8));
}

TEST(IsPrimeTest, Negative)
{
    // This test belongs to the IsPrimeTest test case.

    EXPECT_FALSE(math_func::isPrime(-1));
    EXPECT_FALSE(math_func::isPrime(-2));
    EXPECT_FALSE(math_func::isPrime(INT_MIN));
}

TEST(IsPrimeTest, Trivial)
{
    EXPECT_FALSE(math_func::isPrime(0));
    EXPECT_FALSE(math_func::isPrime(1));
    EXPECT_TRUE(math_func::isPrime(2));
    EXPECT_TRUE(math_func::isPrime(3));
}

TEST(IsPrimeTest, Positive)
{
    EXPECT_FALSE(math_func::isPrime(4));
    EXPECT_TRUE(math_func::isPrime(5));
    EXPECT_FALSE(math_func::isPrime(6));
    EXPECT_TRUE(math_func::isPrime(23));
}