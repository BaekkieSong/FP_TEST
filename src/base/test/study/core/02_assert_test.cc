#include <gtest/gtest.h>

TEST(CaseAssertTest, Assert) {
//  assert(1 < 0);  //runtime error occured!
  assert(1 > 0);
  ASSERT_LT(0, 1);  //<
  ASSERT_LE(0, 0);  //<=
  ASSERT_GT(1, 0);  //>
  ASSERT_GE(1, 1);  //>=
}
TEST(CaseAssertTest, StaticAssert) {
//  static_assert(1 < 0); //compile error occured!
  EXPECT_LT(0, 1);
  EXPECT_GT(1, 0);
  static_assert(1 > 0, "\nshow message if failed\n");
}
