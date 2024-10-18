#include <gtest/gtest.h>
#include "../include/converter.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(1)=="bir");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(13)=="on üç");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(27)=="yirmi yedi");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(38)=="otuz sekiz");
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(77)=="yetmiş yedi");
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(FromIntToString(94)=="doksan dört");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

