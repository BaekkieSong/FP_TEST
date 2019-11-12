#include <iostream>
#include <typeinfo>   //typeid
#include <functional> //std::function

#include <vector>
#include <numeric> //std::accumulate

int answer=42;
//decltype(auto) return_ref() { return &answer; }
auto return_ref() -> decltype(answer)/*->int*/ { return answer; }
auto&& return_forward() { return answer; }
auto return_ans() { return answer; }
const auto& return_const_ref() { return answer; }
void print_data() {
  std::cout << return_ref() << std::endl;
  std::cout << return_forward() << std::endl;
  std::cout << return_ans() << std::endl;
  std::cout << return_const_ref() << std::endl;
  const int a = return_ans();
  std::cout << a << std::endl;
}

template<typename Object, typename Function>
decltype(auto) return_perfect_forward(Object&& object, Function function) {
  return function(std::forward<Object>(object));
}
template<typename T>
decltype(auto) adder(T&& t) {
  return std::forward<T>(t+1);
}
void print_perfect_forward() {
  int a=4;
  std::cout<< "adder:" << return_perfect_forward(a, [](int x) { return x + 1; }) << std::endl;
//  std::cout<< "adder:" << return_perfect_forward(a, adder) << std::endl;
}

int ask() { return 42; }
double d_ask() { return 4.0; }
typedef decltype(ask)* function_ptr;
class convertible_to_function_ptr {
  public:
    //operator decltype(auto)*() {
    operator decltype(ask)*() {
    //operator function_ptr() {
      return ask;
    }
};
class Acc {
  public:
    Acc(int acc):acc_(acc) {};
    int operator()(int a) {
      return acc_ + a;
    }
//    operator decltype(ask)*() {
//      return acc_ + ask();
//    }
  private:
    int acc_;
}; //Acc == [acc_](int a) { return acc_ + a; }
class functor {
  public:
    int operator()(int a) {
      return a;
    }
};
//class acc_add {
//  public:
//    template<typename T>
//    int operator()(T&& t, int a) {
//      return (int)t + a;
//    }
//};
void print_func_ptr() {
  auto func_ptr = &ask;
  auto& func_ref = ask;
  convertible_to_function_ptr func_wrapper;
  std::function<int()> std_function = ask;
  //std::function<int()>* std_function2 = &ask;

  std::cout << "type: " << typeid(ask).name() << ", " << ask() << std::endl;
  std::cout << "type: " << typeid(func_ptr).name() << ", " << func_ptr() << std::endl;
  std::cout << "type: " << typeid(func_ref).name() << ", " << func_ref() << std::endl;
  std::cout << "type: " << typeid(func_wrapper).name() << ", " << func_wrapper() << std::endl;
  std::cout << "type: " << typeid(std_function).name() << ", " << std_function() << std::endl;

  Acc acc(3);
  functor f;
  int a = 3;
  auto ramda = [a](int b) { return a + b; };
  std::cout << "type: " << typeid(acc).name() << ", " << acc(5) << std::endl;
  std::cout << "type: " << f(5) << std::endl;
  std::cout << "type: " << typeid(ramda).name() << ", " << ramda(5) <<std::endl;

  std::vector<int> int_v{1,2,3,4,5};
  std::cout << "acc: "<<std::accumulate(int_v.cbegin(), int_v.cend(), 100, [](int a, int b) { return a + b;}) << std::endl; //a is 100 & b is int_v value
//  std::cout << "acc: "<<std::accumulate(int_v.cbegin(), int_v.cend(), 100, acc_add) << std::endl; //a is 100 & b is int_v value
}

int main(int argc, char** argv) {
  print_data();
  print_perfect_forward();
  print_func_ptr();
  return 0;
}
