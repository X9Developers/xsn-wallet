// Copyright (c) %YEAR The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(CoreTests, CoreTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
