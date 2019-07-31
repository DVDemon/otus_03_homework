#include "lib.h"
#include <gtest/gtest.h>

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(true);
}

TEST(test_02, basic_test_set)
{
   ASSERT_TRUE(true);
}

TEST(test_03, basic_test_set)
{
   ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}