#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include <vector>

TEST(CoreAlgorithmTest, find) {
  std::string str1 = "aaa";
  std::string str2 = "ccc";
  std::vector<std::string> v{"aaa", "ccccccc", "bbb"};

  std::vector<std::string>::iterator result1 = std::find(v.begin(), v.end(), str1);
  auto result2 = std::find(std::begin(v), std::end(v), str2);

  if (result1 != std::end(v)) {
    EXPECT_STREQ(result1->c_str(), "aaa");
  } else {
    EXPECT_STRNE(result1->c_str(), "aaa");
  }

  if (result2 != std::end(v)) {
    EXPECT_STREQ(result1->c_str(), "ccc");
  } else {
    EXPECT_STRNE(result1->c_str(), "ccc");
  }
}

TEST(CoreAlgorithmTest, for_each) {
  int sum = 0;
  int arr[10] = {1,2,3,4,5,6,7,8};
  std::for_each(std::begin(arr),std::end(arr), [&](const int& x) { sum = sum + x;});
  EXPECT_EQ(sum, 36);

  sum = 0;
  std::vector<int> v = {1,2,3,4,5,6,7,8};
  std::for_each(v.cbegin(), v.cend(), [&](const int& x) { sum = sum + x;});
  EXPECT_EQ(sum, 36);
}
