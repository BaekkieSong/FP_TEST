#include <gtest/gtest.h>

//std::move architecture
template<typename T>
typename std::remove_reference<T>::type&& move_semantic(T&& data) {
  //template안에서만 typename 키워드 사용 가능
  using ReturnType = typename std::remove_reference<T>::type&&;
  return static_cast<ReturnType>(data);
}

template <typename T>
T&& forward_semantic(typename std::remove_reference<T>::type& data) {
  return static_cast<T&&>(data);
}

TEST(ModernCoreTest, LRvalue) {
  int i=10;
  int& ri = i;
  int&& uri = 3;
  //int&& uri2 = i;   //rvalue ref(int) cannot bind to lvalue int
  //int&& uri3 = ri;  //rvalue ref(int) cannot bind to lvalue int
  EXPECT_EQ(typeid(int), typeid(i));
  EXPECT_EQ(typeid(int&), typeid(i));
  EXPECT_EQ(typeid(int&&), typeid(i));
  EXPECT_EQ(typeid(int), typeid(ri));
  EXPECT_EQ(typeid(int&), typeid(ri));
  EXPECT_EQ(typeid(int&&), typeid(ri));
  EXPECT_EQ(typeid(int), typeid(uri));
  EXPECT_EQ(typeid(int&), typeid(uri));
  EXPECT_EQ(typeid(int&&), typeid(uri));
}

TEST(ModernCoreTest, Move) {
  int i = 3;
  int&& uri = std::move(i);
  int&& uri2 = move_semantic(uri);

  EXPECT_EQ(i, 3);  //i값이 지워지지 않는다... move는 메모리 이동을 보장하지 않음!
  EXPECT_EQ(uri, i);
  EXPECT_EQ(uri2, uri);
  EXPECT_EQ(typeid(uri), typeid(uri2));
}

TEST(ModernCoreTest, Move_Extension) {
  std::string str = "data";
  std::string str2 = std::move(str);
  EXPECT_EQ(str, "");
  EXPECT_EQ(str2, "data");

  str = "data2";
  std::vector<std::string> str_vec;
  str_vec.push_back(std::move(str));
  EXPECT_EQ(str, "");   //여기선 str값이 지워짐... 메모리까지 move된 상황
  EXPECT_EQ(str_vec[0], "data2");
}


struct A {
  A(){}
  A(const A& obj) { printf("c\n");str = "copied"; }
  A(A&& obj) { printf("m\n");str = "moved"; }
  std::string str;
};
template <typename T>
A wrapper(T&& data) {
  return A(std::forward<T>(data));
}

template <typename T>
A wrapper_semantic(T&& data) {
  return A(forward_semantic<T>(data));
}

TEST(ModernCoreTest, Forward) {
  //std::move convert value to rvalue
  //std::forward convert lvalue to lvalue && rvalue to rvalue

  A a;
  A b = wrapper(a);
  //EXPECT_EQ(wrapper(a).str, "copied");
  EXPECT_EQ(b.str, "copied");
  A c = wrapper(std::move(a));
  //EXPECT_EQ(wrapper(std::move(a)).str, "moved");
  EXPECT_EQ(c.str, "moved");
  EXPECT_EQ(wrapper_semantic(a).str, "copied");
  EXPECT_EQ(wrapper_semantic(std::move(a)).str, "moved");
}
