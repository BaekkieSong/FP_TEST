#include <gtest/gtest.h>

class A {
  public:
    A() { std::cout << "A!!!" << std::endl; }
    A(int i) { std::cout << "A + params!!!" << std::endl; }
    A(std::initializer_list<int> l) { std::cout << "A Initilaized" << std::endl; }
};

class B {
  public:
    B(A a) { std::cout << "B!!!" << std::endl; }
};

//void xx();
TEST(DISABLED_CoreInitializeListTest, Default) {
  A a;  //Test에선 확인 불가... Default Const 불림
  //func declaration
//  A aa();     //OK, but Warning Generated.
  A aaa{};  //Test에선 확인 불가... Default Const 불림
//  A ac(3.5);  //OK, but Warning Generated.
  A ac2(3);
  A ai2{3}; //Can't use Narrow-Conversions
  B b{A()};
}
