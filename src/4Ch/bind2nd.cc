#include <iostream>
#include <typeinfo>   //typeid
#include <functional> //std::function

#include <vector>
#include <numeric> //std::accumulate
#include <string>
#include <algorithm> //std::count_if ,std::sort
#include <ctime> //std::time_t
#include <memory> //std::unique_ptr

#include "common/person.h"

//람다 필터
template <typename T>
void Filter(const std::vector<T>& filter, std::vector<T>& target) {
  target.erase(std::remove_if(target.begin(), target.end(),
        [&filter](const T& item) {
        return std::find(filter.begin(), filter.end(),
            item) == filter.end();
        }),
      target.end());
}

//이항 -> 단항 예제
class greater_than {
  public:
    greater_than(int value) : value_(value){}
    ~greater_than() = default;
    bool operator()(int value) const {
      return value >= value_;
    }
  private:
    int value_;
};
void printGreaterThan() {
  greater_than greater_than_42(42);
  std::cout << "1은 42보다 크다: " << greater_than_42(1) << std::endl;
  std::cout << "50은 42보다 크다: " << greater_than_42(50) << std::endl;
  std::vector<int> int_v{1,10,2,4,50,80,23,45,90,30};
  std::cout << "42보다 큰 값 삭제하기" << std::endl;
  std::cout << "origin: ";
  for (auto it : int_v) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
  int_v.erase(std::remove_if(int_v.begin(),int_v.end(), greater_than(42)),int_v.end());
  std::cout << "filtered: ";
  for (auto it : int_v) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

//bind2nd
template<typename Function, typename Second>
class bind2nd_module {
  private:
    Function function_;
    Second second_;
	public:
	  bind2nd_module(Function function, Second second) : function_(function),
	                                                         second_(second) {
	  }

	  template<typename First>
    auto operator()(First&& first) const -> decltype(function_(std::forward<First>(first), second_)) {
      return function_(std::forward<First>(first), second_);
    }

};
template<typename Function, typename Second>
bind2nd_module<Function, Second> //output
bind2nd(Function&& function, Second&& second) {
  return bind2nd_module<Function, Second>(std::forward<Function>(function), std::forward<Second>(second));
}
void printBind2nd() {
  std::vector<int> int_v{1,10,2,4,50,80,23,45,90,30};
  std::vector<int> copy_v(int_v.size());
  std::copy_if(int_v.cbegin(),int_v.cend(),copy_v.begin(), bind2nd(std::greater<int>(), 55));
  std::cout << "copied: ";
  for(auto it : copy_v) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}


int main(int argc, char** argv) {
  printGreaterThan();
  printBind2nd();
  return 0;
}
