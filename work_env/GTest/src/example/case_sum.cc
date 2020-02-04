#include <gtest/gtest.h>

int sum(int a, int b) {
  return a + b;
}

TEST(CASE_SUM, SUM_TWO_VALUE) {
  EXPECT_EQ(3, sum(1, 2));
}

