// Copyright (c) %YEAR The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
//#include <bitcoin/bitcoin.hpp>
#include <iostream>

using namespace testing;

TEST(CoreTests, CoreTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(CoreTests, LibbitcoinTest)
{
//    const auto block = bc::chain::block::genesis_mainnet();
//    const auto& tx = block.transactions().front();
//    const auto& input = tx.inputs().front();
//    const auto script = input.script().to_data(false);
//    std::string message(script.begin() + sizeof(uint64_t), script.end());
//    std::cout << message << std::endl;
}
