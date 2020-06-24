#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(VectorTest, vectorstring) {
  std::vector<std::string> str_vec;
  int line = 0;
  EXPECT_EQ(str_vec.size(), 0);
  if (str_vec.empty())
    str_vec.push_back(std::string());
  str_vec.at(line) += 'c';
  EXPECT_STREQ(str_vec.at(line).c_str(), "c");
}
