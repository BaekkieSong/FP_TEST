#include <gtest/gtest.h>
#include <cstring>// == string.h
//cstring 특성상 char*에 최적화 되어 있음... 원하는 부분 복사 같은게 힘듦

class CStringTest : public ::testing::Test {
  protected:
    void SetUp() override {
      str_ = "test string";
      pc_ = new char[20];
      std::strcpy(pc_,str_.c_str());
      pctest_ = new char[20];
      std::strcpy(pctest_,str_.c_str());
      std::memcpy(carr_, str_.c_str(), str_.size() + 1);
    }
    void TearDown() override{
      delete[] pc_;
      delete[] pctest_;
    }

    std::string str_;
    char* pc_;
    char* pctest_;
    char carr_[20];
};

TEST_F(CStringTest, Default) {
  EXPECT_EQ(str_, "test string");
  EXPECT_EQ(str_.size(), std::strlen(pc_));
  EXPECT_EQ(std::strlen(pc_), std::strlen(carr_));
  EXPECT_NE(pc_, pctest_);
}

//std::string::c_str()은 const char*로 리턴되므로 Copy dest로 사용이 불가하다는 것에 유의
class CStringTestCopying : public CStringTest {};

//[](void* dest, const void* src, size_t num) --> void*(dest)
TEST_F(CStringTestCopying, Memcpy) {
  char* pc = new char[std::strlen(carr_)+1];//sizeof(carr_)/sizeof(char)+1];
  std::memcpy(pc, carr_, std::strlen(carr_)+1);
  size_t pos = 0;
  while(pos != '\0')
    EXPECT_EQ(pc[pos], carr_[pos]);
  EXPECT_STREQ(pc, carr_);
  delete[] pc;
  std::cout << std::strlen(pc_) << std::endl;
}

//[](void* dest, const void* src, size_t num) --> void*(dest)
TEST_F(CStringTestCopying, Memmove) {
  std::memmove(pc_+8, pc_, 4);
  //remove back of (pc_ + 9)
  //insert 'pc_ ~ pc_ + 4' at (pc_ + 8)
  EXPECT_STREQ(pc_, "test strtest");
}

//[](char* dest, const char* src) --> char*
TEST_F(CStringTestCopying, Strcpy) {
  char* pcarr = new char[str_.size() + 1];
  std::strcpy(pcarr, str_.c_str());
  EXPECT_STREQ(pcarr, str_.c_str());
  delete[] pcarr;
  //EXPECT_STREQ(pcarr, str_);
  char carr[str_.size() + 1];
  std::strcpy(carr, str_.c_str());
  EXPECT_STREQ(carr, str_.c_str());
}

//[](char* dest, const char* src, size_t num) --> char*
TEST_F(CStringTestCopying, Strncpy) {
  char* pcarr = new char[5];
  std::strncpy(pcarr, str_.c_str(), 5);
  EXPECT_STREQ(pcarr, "test ");
  delete[] pcarr;
}

class CStringTestConcatenation : public CStringTest {};

//[](char* dest, const char* src) --> char*
//~=(std::string)str.insert(str.back(), src);
TEST_F(CStringTestConcatenation, Strcat) {
  char* pcarr = new char[50];
  std::strcat(pcarr, pc_);  //need to initializing.
  std::strcat(pcarr, " addcat");
  std::strcat(pcarr, " addcat2");
  EXPECT_STRNE(pcarr, "test string addcat addcat2"); //Error. can't get begin point.

  std::strcpy(pcarr, pc_);
  std::strcat(pcarr, " addcat");
  std::strcat(pcarr, " addcat2");
  EXPECT_STREQ(pcarr, "test string addcat addcat2");
  delete[] pcarr;
}

