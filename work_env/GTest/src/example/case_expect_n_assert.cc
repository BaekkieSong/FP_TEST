#include <gtest/gtest.h>

TEST(CASE_EXPECT, FALSE) {
//  EXPECT_TRUE(false);
  EXPECT_FALSE(false);
}

TEST(CASE_EXPECT, EQ) {
  EXPECT_EQ(true, true);
  EXPECT_EQ(false, false);
}

TEST(CASE_EXPECT, TRUE) {
  EXPECT_TRUE(true);
//  EXPECT_FALSE(true);
}

TEST(CASE_ASSERT, FALSE) {
  ASSERT_FALSE(false);
}

TEST(CASE_ASSERT, EQ) {
  ASSERT_EQ(true, true);
  ASSERT_EQ(false, false);
}

TEST(CASE_ASSERT, TRUE) {
  ASSERT_TRUE(true);
}
