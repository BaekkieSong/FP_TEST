#include <gtest/gtest.h>
#include <fstream>
//#include <iostream>
#include <string>

class CaseFstream : public::testing::Test {
  protected:
    void SetUp() override {
      file_path_ = "fstream_file.txt";
    }
    void TearDown() override {
    }

    std::string file_path_;
};

TEST_F(CaseFstream, Default) {
  //write
  std::ofstream write_file(file_path_.data());
  if(write_file.is_open()) {
    write_file << "text\n";
    write_file.close();
  }

  //read
  std::ifstream read_file(file_path_.data());
  if(read_file.is_open()) {
    std::string line;
    while(getline(read_file, line)) {
      EXPECT_EQ(line, "text");
    }
  }
  read_file.close();
}

TEST_F(CaseFstream, AddedText) {
  //write
  std::ofstream write_file(file_path_.data());
  if(write_file.is_open()) {
    write_file << "text\n";
    write_file.close();
  }
  //write added
  write_file.open(file_path_.data(), std::ios::app);
  if(write_file.is_open()) {
    write_file << "second text line\n";
    write_file.close();
  }

  //read
  std::ifstream read_file(file_path_.data());
  if(read_file.is_open()) {
    unsigned int count_line = 0;
    std::string line;
    while(getline(read_file, line)) {
      if (count_line++ == 0)
        EXPECT_EQ(line, "text");
      else if (count_line++ == 1)
        EXPECT_EQ(line, "second text line");
    }
  }
}

TEST_F(CaseFstream, Fstream) {
  std::fstream f_file;
  system("rm -rf fstream_file.txt");
  f_file.open(file_path_.data());
  EXPECT_EQ(f_file.is_open(), false);
  f_file.open(file_path_.data(), std::ios::in);
  EXPECT_EQ(f_file.is_open(), false);

  f_file.open(file_path_.data(), std::ios::out);
  if (f_file.is_open()){
    f_file << "test text\n";
    f_file.close();
  }

  f_file.open(file_path_.data(), std::ios::in);
  if (f_file.is_open()) {
    EXPECT_EQ(f_file.eof(), false);
    std::string line;
    while(getline(f_file, line)) {  //don't read Empty Line ""
      EXPECT_EQ(line, "test text");
    }
    f_file.close();
  }
}

TEST_F(CaseFstream, Fstream2) {
  std::fstream f_file(file_path_.data(), std::ios::in);
  if (f_file.is_open()) {
    unsigned int count_line = 0;
    std::string line;
    while(!f_file.eof()) {  //read Empty Line. {"test text", "", EOF}
      getline(f_file, line);
      if (count_line++ == 0)
        EXPECT_EQ(line, "test text");
      else if (count_line++ == 1)
        EXPECT_EQ(line, "");
    }
  }
}
