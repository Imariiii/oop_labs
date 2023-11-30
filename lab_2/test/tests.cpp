#include <gtest/gtest.h>
#include "../include/decarray.h"

TEST(decimalConstructor, defaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.getSize(), 0);
}

TEST(decimalConstructor, sizeAndValueConstructor) {
    Decimal d(5, 7);
    EXPECT_EQ(d.getSize(), 5);
    EXPECT_EQ(d.toString(), "77777");
}

TEST(decimalConstructor, initializerListConstructor) {
    Decimal d({1, 2, 3, 4, 5});
    EXPECT_EQ(d.getSize(), 5);
    EXPECT_EQ(d.toString(), "12345");
}

TEST(decimalConstructor, stringConstructor) {
    Decimal d("666");
    EXPECT_EQ(d.getSize(), 3);
    EXPECT_EQ(d.toString(), "666");
}

TEST(decimalConstructor, invalidStringConstructor) {
    ASSERT_THROW(Decimal("123asd45"), std::invalid_argument);
}

TEST(decimalConstructor, moveConstructor) {
    Decimal original("123");
    Decimal moved(std::move(original));

    
    EXPECT_EQ(original.getSize(), 0);
    
    EXPECT_EQ(moved.getSize(), 3);
    EXPECT_EQ(moved.toString(), "123");
}

TEST(decimalOperators, assign) {
    Decimal d("666");
    Decimal d1 = d;
    EXPECT_EQ(d1.getSize(), 3);
    EXPECT_EQ(d1.toString(), "666");
}


TEST(decimalOperators, plusOperator) {
    Decimal d("5816");
    Decimal d1("3762");
    Decimal result = d + d1;
    EXPECT_EQ(result.getSize(), 4);
    EXPECT_EQ(result.toString(), "8588");
}

TEST(decimalOperators, minusOperator) {
    Decimal d("9999");
    Decimal d1("762");
    Decimal result = d - d1;
    EXPECT_EQ(result.getSize(), 4);
    EXPECT_EQ(result.toString(), "2379");
}


TEST(decimalOperators, minusOperatorTwo) {
    Decimal d("123");
    Decimal d1("123");
    Decimal result = d - d1;
    EXPECT_EQ(result.getSize(), 1);
    EXPECT_EQ(result.toString(), "0");
}

TEST(decimalOperators, minusOperatorThree) {
    Decimal d("123");
    Decimal d1("99999");
    try {
        Decimal res = d1 - d;
    } catch (const std::runtime_error& e) {
        ASSERT_STREQ(e.what(), "Result is a negative number");
    }

}


TEST(decimalOperators, lessThanOperator) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal d3("123");
    Decimal d4("1234");
    EXPECT_TRUE(d1 < d2);
    EXPECT_FALSE(d2 < d1);
    EXPECT_FALSE(d3 < d1);
    EXPECT_TRUE(d2 < d4);
}

TEST(decimalOperators, greaterThanOperator) {
    Decimal d1("789");
    Decimal d2("123");
    Decimal d3("123");
    EXPECT_TRUE(d1 > d2);
    EXPECT_FALSE(d2 > d1);
    EXPECT_FALSE(d2 > d3);
}

TEST(decimalOperators, lessThanOrEqualOperator) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal d3("123");
    Decimal d4("999");
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 <= d3);
    EXPECT_FALSE(d4 <= d1);
}

TEST(decimalOperators, greaterThanOrEqualOperator) {
    Decimal d1("789");
    Decimal d2("123");
    Decimal d3("789");
    EXPECT_TRUE(d1 >= d2);
    EXPECT_TRUE(d1 >= d3);
}

TEST(decimalOperators, equalityOperator) {
    Decimal d1("123");
    Decimal d2("123");
    Decimal d3("456");
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(decimalOperators, inequalityOperator) {
    Decimal d1("123");
    Decimal d2("123");
    Decimal d3("456");
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 != d3);
}


TEST(decimalOperators, preIncrementOperator) {
    Decimal d("123");
    ++d;
    ASSERT_TRUE(d.getSize() == 3);
    ASSERT_TRUE(d.toString() ==  "223");
}

TEST(decimalOperators, preIncrementOperatorTwo) {
    Decimal d("0");
    ++d;
    ASSERT_TRUE(d.getSize() == 1);
    ASSERT_TRUE(d.toString() ==  "1");
}

TEST(decimalOperators, postIncrementOperator) {
    Decimal d1("748");
    Decimal result = d1++;
    ASSERT_TRUE(result.getSize() == 3);
    ASSERT_TRUE(result.toString() == "748");
    ASSERT_TRUE(d1.getSize() == 3);
    ASSERT_TRUE(d1.toString() == "848");
}

TEST(decimalOperators, preDecrementOperator) {
    Decimal d("777");
    --d;
    EXPECT_EQ(d.getSize(), 3);
    EXPECT_EQ(d.toString(), "677");
}


TEST(decimalOperators, postDecrementOperatorTwo) {
    Decimal d("666");
    Decimal result = d--;
    EXPECT_EQ(result.getSize(), 3);
    EXPECT_EQ(result.toString(), "666");
    EXPECT_EQ(d.getSize(), 3);
    EXPECT_EQ(d.toString(), "566");
}

TEST(decimalOperators, postDecrementOperatorThree) {
    Decimal d("666");
    Decimal result = d--;
    EXPECT_EQ(result.getSize(), 3);
    EXPECT_EQ(result.toString(), "666");
    EXPECT_EQ(d.getSize(), 3);
    EXPECT_EQ(d.toString(), "566");
}

TEST(decimalOperators, preDecrementOperatorFour) {
    Decimal d("1");
    --d;
    EXPECT_EQ(d.getSize(), 1);
    EXPECT_EQ(d.toString(), "0");
}


TEST(decimalOperators, outputOperator) {
    Decimal d("789");
    testing::internal::CaptureStdout();
    std::cout << d;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "789");
}


TEST(decimalMethods, printNum) {
    Decimal d1("12345");
    testing::internal::CaptureStdout();
    d1.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "54321\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}