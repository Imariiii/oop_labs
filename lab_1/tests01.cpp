#include <gtest/gtest.h>
#include "max_n.h"

TEST(test_01, basic_test_set) {
    ASSERT_TRUE(max_n(10,11)==10);
}

TEST(test_02, basic_test_set) {
    ASSERT_TRUE(max_n(5,24)==20);
}

TEST(test_03, basic_test_set) {
    ASSERT_TRUE(max_n(3,100)==99);
}

TEST(test_04, basic_test_set) {
    ASSERT_TRUE(max_n(12,12)==12);
}

TEST(test_05, basic_test_set) {
    ASSERT_TRUE(max_n(15,12)==0);
}

TEST(test_06, basic_test_set) {
    ASSERT_TRUE(max_n(1,1)==1);
} 

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}