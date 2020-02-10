#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstring> //strcpy
#include <algorithm>

class CaseStrTest : public ::testing::Test {
  protected:
    void SetUp() override {
      text = "test string";
    }
    void TearDown() override {}

    std::string text;
};

TEST_F(CaseStrTest, StrAssign) {
  EXPECT_EQ(text, "test string");
}


TEST(CaseStrDefault, StrContructor) {
  std::string s1 = "default string";
  std::string s2;
  std::string s3(s1);
  std::string s4(s1, 2, 5); //fault
  std::string s5("test string");
  std::string s6_1("test string", 4); //test
  std::string s6_2(s5, 5);  //string  s5.begin()+5
  std::string s7(5, 'x');
  std::string s8(5, 42);  //ASCII 42 = *
  std::string s9(s1.begin(), s1.begin()+7); //default
  EXPECT_EQ(s1, "default string");
  EXPECT_EQ(s2, "");
  EXPECT_EQ(s2, std::string());
  EXPECT_EQ(s3, "default string");
  EXPECT_EQ(s4, "fault");
  EXPECT_EQ(s5, "test string");
  EXPECT_EQ(s6_1, "test");
  EXPECT_EQ(s6_2, "string");
  EXPECT_EQ(s7, "xxxxx");
  EXPECT_EQ(s8, "*****");
  EXPECT_EQ(s9, "default");
}

//return iterator
TEST(CaseStrIterator, StrIter) {
  std::string str("test string");
  std::string result;
  for(std::string::iterator it = str.begin(); it!= str.end(); ++it) {
    result += *it;
    std::cout << *it;
  }
  std::cout << std::endl;
  EXPECT_EQ(str, result);
}

TEST(CaseStrIterator, StrReverseIter) {
  std::string str("test string");
  std::string result;
  for(std::string::reverse_iterator rit = str.rbegin(); rit!= str.rend(); ++rit) {
    result += *rit;
    std::cout << *rit;
  }
  std::cout << std::endl;
  EXPECT_EQ(result, "gnirts tset");
}

TEST(CaseStrIterator, StrConstIter) {
  std::string str("test string");
  for(auto it = str.cbegin(); it!=str.cend(); ++it)
    std::cout << *it;
  std::cout << std::endl;
  for(auto rit = str.crbegin(); rit!=str.crend(); ++rit)
    std::cout << *rit;
  std::cout << std::endl;
  EXPECT_EQ(str.cbegin(), str.begin());
}

//return size_t
TEST(CaseStrCapacity, StrSize) {
  std::string str("test string");
  //size
  EXPECT_EQ(str.size(), 11);
  //length
  EXPECT_EQ(str.length(), 11);
  //max_size
  EXPECT_GT(str.max_size(), 100);
}

TEST(CaseStrCapacity, StrCapacity) {
  //capacity
  std::string str("test string");
  EXPECT_EQ(str.capacity(), 15);

  std::string str2;
  EXPECT_EQ(str2.capacity(), 15);
  str2 = str;
  EXPECT_EQ(str2.capacity(), 15);
  str2 += " added string";
  EXPECT_EQ(str2.capacity(), 30);
  str2 += " added string";
  EXPECT_EQ(str2.capacity(), 60);
  str2 += str2;
  EXPECT_EQ(str2.capacity(), 120);
}

TEST(CaseStrCapacity, StrResize) {
  //resize
  std::string str("test string");
  EXPECT_EQ(str.size(), 11);
  str.resize(str.size()+2, '!');
  EXPECT_EQ(str.size(), 13);
  str.resize(8);
  EXPECT_EQ(str.size(), 8);
  EXPECT_EQ(str.capacity(), 15);
  EXPECT_EQ(str, "test str");
  str.resize(11);
  EXPECT_NE(str, "test str\0\0\0"); //NULL value. It's defferent with str.
}

TEST(CaseStrCapacity, StrReserve) {
  std::string str2;
  str2.reserve(33);
  EXPECT_EQ(str2.capacity(), 33);

  std::string str;
  str.reserve(130);
  EXPECT_EQ(str.capacity(), 130);
  str.reserve(10);
  EXPECT_EQ(str.capacity(), 15); //capacity minimum: 15
  str.reserve(20);
  EXPECT_EQ(str.capacity(), 30);
  str.reserve(42);
  EXPECT_EQ(str.capacity(), 60);
  str.reserve(70);
  EXPECT_EQ(str.capacity(), 120);
  str.reserve(125);
  EXPECT_EQ(str.capacity(), 240);
  str.reserve(16);
  EXPECT_EQ(str.capacity(), 16);
  str.reserve(71);
  EXPECT_EQ(str.capacity(), 71);
  str.reserve(234);
  EXPECT_EQ(str.capacity(), 234);
}

TEST(DISABLED_CaseStrCapacity, StrClear) {
  std::string str;
  std::cout << "Input str. \n"
            << "Enter: next line \n"
            << ". : exit \n"
            << "================ \n";
  char c;
  do {
    c = std::cin.get();
    if (c != '.' && c !='\n') {
      str += c;
    } else if (c=='\n') {
      std::cout << str << std::endl;
      str.clear();
      EXPECT_EQ(str, "");
    }
  } while(c!='.');
}

TEST(CaseStrCapacity, StrClearDeafult) {
  std::string str = "str";
  EXPECT_EQ(str, "str");
  str.clear();
  EXPECT_EQ(str, "");
}

TEST(CaseStrCapacity, StrShrinkToFit) {
  std::string str="The test string using shrink_to_fit for capacity.";  //str.size()==49
  EXPECT_EQ(str.capacity(), 49);

  std::string str2 = str;
  str2.resize(21);
  EXPECT_EQ(str2, str.substr(0,21));  //why?????? not 0,20????
  EXPECT_EQ(str2.capacity(), 49);
  str2.shrink_to_fit();
  EXPECT_EQ(str2.capacity(), 21);

  std::string str3;
  EXPECT_EQ(str3.capacity(), 15);
  str3.shrink_to_fit();
  EXPECT_EQ(str3.capacity(), 15);
  str3 = "eee";
  str3.shrink_to_fit();
  EXPECT_EQ(str3.capacity(), 15);
}

//return char&
TEST(CaseStrElement, StrElement) {
  std::string str("test string");
  int count = 0;
  for (auto c : str) {
    EXPECT_EQ(c, str[count]);
    EXPECT_EQ(c, str.at(count));
    ++count;
  }
  str.back() = 'k';
  EXPECT_EQ(str.back(), 'k');
  str.front() = 'T';
  EXPECT_EQ(str.front(), 'T');
  EXPECT_EQ(str, "Test strink");
}

TEST(CaseStrModifier, StrAppend) {
  std::string str = "test string";
  std::string added = " added";
  str.append(added); //test string added
  str.append(added,0,4); //test string added add
  str.append("what the hell", 4); //test string added addwhat
  str.append("**"); //test string added addwhat**
  str.append(3u,'-'); //test string added addwhat??---
  str.append(added.begin()+2, added.begin()+4); //test string added addwhat**---dd
  //str.append<char>(3,'c'); //test string added addwhat**---ddccc
  //str.append<int>(3,0x2E); //test string added addwhat**---dd...
  EXPECT_EQ(str, "test string added addwhat**---dd");
}

TEST(CaseStrModifier, StrPush) {
  std::string str = "test string";
  str.push_back('!');  //char c
  EXPECT_EQ(str, "test string!");
}

TEST(CaseStrModifier, StrAssign) {
  std::string str = "test string";
  std::string base = "Just do it for yourself!";
  str.assign(base);
  EXPECT_EQ(str, "Just do it for yourself!");
  str.assign(base, 5, 5);
  EXPECT_EQ(str, "do it");
  str.assign(base.begin(), base.begin() + 4);
  EXPECT_EQ(str, "Just");
  str.assign("raw text");
  EXPECT_EQ(str, "raw text");
  str.assign("raw text", 3);
  EXPECT_EQ(str, "raw");
  str.assign(5, '*');
  EXPECT_EQ(str, "*****");
}

TEST(CaseStrModifier, StrInsert) {
  std::string str = "test string";
  std::string base = "Just do it for yourself!";
  str.insert(str.size(), base);
  EXPECT_EQ(str, "test stringJust do it for yourself!");
  std::string base2 = "...?---";
  str.insert(str.end() - 1, base2.begin(), base2.begin()+4);
  EXPECT_EQ(str, "test stringJust do it for yourself...?!");
  str.insert(4, "2, this");
  EXPECT_EQ(str, "test2, this stringJust do it for yourself...?!");

}

TEST(CaseStrModifier, StrErase) {
  std::string str = "test string";
  str.erase(9,11);
  EXPECT_EQ(str, "test stri");
  str.erase(str.begin() + 5); //delete only selected char
  EXPECT_EQ(str, "test tri");
  str.erase(str.begin() + 5, str.end() -1);
  EXPECT_EQ(str, "test i");
}

TEST(CaseStrModifier, StrReplace) {
  std::string str = "my test is fantastic.";
  std::string replaced = "page";
  std::string getsubstr = "aaa bbb ccc";
  //pos
  str.replace(3, 4, replaced); //my page is fantastic.
  str.replace(8, 2, getsubstr, 4, 3); //my page bbb fantastic.
  str.replace(0, 3, "The "); //The page bbb fantastic.
  str.replace(4, 4, "pagestrike", 5); //The pages bbb fantastic.
  str.replace(10, 3, 5, 'a'); //The pages aaaaa fantastic.
  EXPECT_EQ(str, "The pages aaaaa fantastic.");
}

TEST(CaseStrModifier, StrReplaceIter) {
  std::string str = "my test is fantastic.";
  std::string replaced = "dongdongju";
  //iterators
  //diff pos & iter
  /*
   begin() pos 7
    ↓      ↓
     abcdefg
     ↑      ↑
   pos 0  begin()+7
  */
  str.replace(str.begin()+3, str.begin()+7, replaced); //my dongdongju is fantastic.
  str.replace(str.begin()+3, str.end()-2, "do"); //my doc.
  str.replace(str.begin()+1, str.begin()+4, "ost power",3); //mostoc.
  str.replace(str.begin()+4, str.begin()+4, 4, 'p'); //mostppppoc.
  str.replace(str.begin(), str.begin()+4, replaced.begin(), replaced.begin()+4); //dongppppoc.
  EXPECT_EQ(str, "dongppppoc.");
}

TEST(CaseStrModifier, StrSwap) {
  std::string str = "test string";
  std::string changed = "changed string";
  str.swap(changed);
  EXPECT_EQ(str, "changed string");
  EXPECT_EQ(changed, "test string");
}

TEST(CaseStrModifier, StrPop) {
  std::string str = "test string!";
  str.pop_back();
  EXPECT_EQ(str, "test string");
}

//return const char*
TEST(CaseStrOperation, StrCStr) {
  std::string str = "test string";
  char* c_str = new char[str.size()+1];
  //str.c_str() return const char*
  std::strcpy(c_str, str.c_str());
  char* p = std::strtok(c_str, " ");
  EXPECT_EQ(p, c_str);
  while(p) {
    std::cout << p << '\n';
    p = std::strtok(NULL, " ");
    //EXPECT_EQ(p, &c_str[5]);
  }
  delete[] c_str;
}

//return const char*
TEST(CaseStrOperation, StrData) {
  std::string str = "test string";
//  char* c_str = new char[str.size()+1]{"test string"}; //doesn't work in C++11
  char* c_str = new char[str.size()+1];
  std::strcpy(c_str, str.c_str());
  EXPECT_EQ(str.size(), std::strlen(c_str));
  char* cpied_str = new char[12]; //need to assign memory
  //str.data() return const char*
  memcpy(cpied_str, str.data(), str.length());
  std::cout << str.c_str() << ", " << c_str << ", " << cpied_str <<std::endl;
  EXPECT_EQ(str, cpied_str);
  EXPECT_NE(cpied_str, c_str); //difference cstring although their actual data are same
  EXPECT_EQ(sizeof(cpied_str), sizeof(c_str));
  delete[] c_str;
  delete[] cpied_str;
}

//return allocator<char>
TEST(CaseStrOperation, StrAllocator) {
  std::string str;
  EXPECT_EQ(sizeof(char), sizeof(str.get_allocator()));
  EXPECT_NE(sizeof(int), sizeof(str.get_allocator()));
}

TEST(CaseStrOperation, StrCopy) {
  std::string str = "test string";
  char buffer[20];
  std::size_t length = str.copy(buffer, 3,5); //char*, len, pos ????
  buffer[length] = '\0';
  std::cout << "buffer: " << buffer << std::endl;
  EXPECT_EQ(sizeof(buffer)/sizeof(char), 20);
  str = buffer;
  EXPECT_EQ(str, "str");
}

//return size_t []({const string&, const char*, char}, {size_t == pos == 0}, {size_t == n})
TEST(CaseStrOperation, StrFind) {
  std::string base = "How, can, i, find it that is the great factory machine...!";
  std::string find_str = "that";
  std::size_t pos = base.find(find_str);
  EXPECT_NE(pos, std::string::npos);
  EXPECT_EQ(pos, 21);
  pos = base.find("achine", pos+1, 2); //find "ac" --> f"ac"tory
  EXPECT_EQ(pos, 40);
  pos = base.find(',');
  EXPECT_EQ(pos, 3);
  pos = base.find("great");
  EXPECT_EQ(pos, 33);
}

TEST(CaseStrOperation, StrRFind) {
  std::string base = "GO GO GO, Radet GO. Fire!!!!";
  EXPECT_EQ(base.rfind("GO"), 16);
}

TEST(CaseStrOperation, StrFindOf) {
  std::string base = "bbbbbcccccdddddeeeeefffffggggghhhhhiiiiijjjjjkkkkk";
  std::size_t pos = base.find_first_of("aeiou");
  EXPECT_EQ(pos, 15);
  pos = base.find_last_of("aeiou");
  EXPECT_EQ(pos, 39);

  std::string filename = "chrome/browser/chrome/chrome.exe";
  pos = filename.find_last_of('/');
  auto exename = filename.substr(pos + 1);  //only (pos, len) --> string. iter X
  EXPECT_EQ(exename, "chrome.exe");
}

TEST(CaseStrOperation, StrFindNotOf) {
  std::string base = "my name is Jone-Myster.";
  std::transform(base.begin(), base.end(), base.begin(), [](char c) {return std::tolower(c);});

  std::string alpabet = "abcdefghijklmnopqrstuvwxyz";
  std::string space = " ";
  std::string set = alpabet + space;
  std::size_t pos = base.find_first_not_of(set);
  EXPECT_EQ(pos, 15);

  pos = base.find_last_not_of(set);
  EXPECT_EQ(pos, base.size()-1);
}

TEST(CaseStrOperation, StrSubstr) {
  std::string str = "test string";
  auto string_str = str.substr(5, 3);
  EXPECT_EQ(string_str, "str");
  auto string_string = str.substr(5);
  EXPECT_EQ(string_string, "string");
}

//[]({const string&, const char*})
//[]({pos, len, {const string&, const char*}, pos, len) --> int
TEST(CaseStrOperation, StrCompare) {
  std::string str1 = "aaa datapath";
  std::string str2 = "bbb datapath";
  EXPECT_EQ(str1.compare(str2) < 0, true);  //a < b
  EXPECT_EQ(str2.compare(str1) > 0, true);
  EXPECT_EQ(str1.compare("aaa datapath") == 0, true);
  EXPECT_EQ(str1.compare(4, 8, "datapath"), 0);
  EXPECT_EQ(str1.compare(4, 8, str2, 4, 8), 0);
  EXPECT_EQ(str1.compare(4, 4, "dataAAAA", 4), 0);  //data
  EXPECT_EQ(str1.compare(5, 3, "FataAAAA", 1, 3), 0); //ata
}

TEST(DISABLED_CaseStrInputStr, StrGetline) {
  std::string test_str;
  //[](istream&, string&, char == '\n') --> istream&
  std::getline(std::cin, test_str);//, 'p');
  std::cout << test_str.c_str() << std::endl;
}
