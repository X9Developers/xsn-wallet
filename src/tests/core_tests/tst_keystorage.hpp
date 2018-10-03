#ifndef TST_KEYSTORAGE_HPP
#define TST_KEYSTORAGE_HPP

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <Storage/KeyStorage.hpp>

using namespace testing;

class KeyStorageTest : public ::testing::Test
{
protected:

    KeyStorage storage;

    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
    }
};

TEST_F(KeyStorageTest, PrivateKeyPathDerivation)
{
    for(unsigned coinType = 0; coinType < 1000; ++coinType)
    {
        for(unsigned accountIndex = 0; accountIndex < 100; ++accountIndex)
        {
            const unsigned keysCount = 10;

            for(unsigned i = 0; i < keysCount; ++i)
            {
                ExtendedKeyPathBip44 expectedValue(coinType, accountIndex, false);
                expectedValue.addChild(i);
                auto actualValue = storage.deriveNewChildKey(coinType, accountIndex, false).first;
                ASSERT_EQ(expectedValue, actualValue) << "BIP44 path doesn't match expected: " << expectedValue.toString().toStdString() << " actual: " << actualValue.toString().toStdString();
            }

        }
    }
}

#endif // TST_KEYSTORAGE_HPP
