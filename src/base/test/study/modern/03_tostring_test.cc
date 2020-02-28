#include <gtest/gtest.h>

TEST(ModernToStringTest, to_string) {
  double d = 12.123456789876;
  EXPECT_EQ(std::to_string(d), "12.123457");
  std::stringstream sstr;
  sstr << std::setprecision(9) << d;
  std::string str = sstr.str();
  EXPECT_EQ(str, "12.1234568");
  std::stringstream sstr2;
  sstr2 << std::setprecision(15) << d;
  std::string str2 = sstr2.str();
  EXPECT_EQ(str2, "12.123456789876");
}
