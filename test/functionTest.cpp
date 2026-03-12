#include <gtest/gtest.h>
#include "../function/function.h"


class FunctionTest : public testing::Test {
protected:
    FunctionProvider provider;
    FunctionTest() {

    }
    ~FunctionTest() {

    }
};

TEST_F(FunctionTest, collatzStepsTest) {
    ASSERT_EQ(provider.collatzSteps(9), 19);
    ASSERT_EQ(provider.collatzSteps(97), 118);
    ASSERT_EQ(provider.collatzSteps(871), 178);
    ASSERT_EQ(provider.collatzSteps(6171), 261);
    ASSERT_EQ(provider.collatzSteps(77031), 350);
    ASSERT_EQ(provider.collatzSteps(837799), 524);
    ASSERT_EQ(provider.collatzSteps(8400511), 685);
    ASSERT_EQ(provider.collatzSteps(63728127), 949);
    ASSERT_EQ(provider.collatzSteps(670617279), 986);
    ASSERT_EQ(provider.collatzSteps(9780657630), 1132);
    ASSERT_EQ(provider.collatzSteps(75128138247), 1228);
    ASSERT_EQ(provider.collatzSteps(989345275647), 1348);
}

TEST_F(FunctionTest, leibnizPi) {
    ASSERT_EQ(provider.leibnizPi(0), 4);
    ASSERT_NEAR(provider.leibnizPi(10000), 3.14159, 0.0005);
    ASSERT_NEAR(provider.leibnizPi(1000000), 3.14159, 0.0005);
}

TEST_F(FunctionTest, eApproxTest) {
    ASSERT_EQ(provider.eApprox(0), 1);
    ASSERT_NEAR(provider.eApprox(10000), 2.71828, 0.0001);
}