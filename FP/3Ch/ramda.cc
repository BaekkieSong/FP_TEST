#include <iostream>
#include <typeinfo>   //typeid
#include <functional> //std::function

#include <vector>
#include <numeric> //std::accumulate
#include <string>
#include <algorithm> //std::count_if ,std::sort
#include <ctime> //std::time_t
#include <memory> //std::unique_ptr

#include "person.h"

//람다 기본
void print_copy() {
  auto persons = getPersons();
  std::vector<Person> filtered_persons;
  copy_if(persons.cbegin(), persons.cend(), std::back_inserter(filtered_persons), [](Person person) { return person.age() > 25; });
  std::cout << "filtered: " << filtered_persons.size() << std::endl;
}

//this를 캡처하는 클래스 내부 람다
void print_gender_count() {
  GenderGroup group(getPersons());
  std::cout << "nums: " << group.getNumGenders(Person::Gender::male) << std::endl;
  std::cout << "same_genders(female): " << group.count_same_gender_persons(Person::Gender::female) << std::endl;
  std::cout << "same_genders(male): " << group.count_same_gender_persons(Person::Gender::male) << std::endl;
}

//가변 람다 (mutable)
void print_variable_ramda() {
  int count = 0;
  std::vector<std::string> words{"Hello", "World", "FP", "for", "check", "Upper", "count"};

  std::for_each(words.cbegin(), words.cend(),
      [count](const std::string& word) mutable {
        if(::isupper(word[0]))
          ++count;
        std::cout << "Upper count(internal): " << count << std::endl;
      });
  std::cout << "Warning: mutable count apply in ramda only" <<std::endl;
  std::cout << "Upper count(external): " << count << std::endl;
}

//일반 람다 캡처(unique_ptr변수의 캡처, 변수 생성과 동시에 캡처(타입추론적용))
void print_general_ramda_capture() {
  std::unique_ptr<Person> person = std::make_unique<Person>("name", 30, Person::Gender::male);

  [person = std::move(person), time = std::time(nullptr)]() {
    std::cout << std::asctime(std::localtime(&time));// <<std::endl;
    std::cout << "person age: " << person->age() << std::endl;
  }();

  if (person)
    std::cout << "be moved person age: " << person->age() << std::endl;
  else
    std::cout << "no memory" << std::endl;
}

//일반 람다(~=template)
void print_generic_ramda() {
  auto older_age = [limit=42](auto&& object) { return object.age() >= limit; };

  //c++20 style
  //auto counter = [count=0]<typename T>(T first, T second) {
  auto counter = [count=0](auto first, decltype(first) second) {
    return first + (int)(first <= second);
  };

  Person::Gender gender = Person::Gender::female;

  auto persons = getPersons();
  std::cout << "older 42 persons count: "
            << std::count_if(persons.cbegin(), persons.cend(), older_age) << std::endl;

  //다음 값이 이전값 pos+1보다 크면 1씩 증가
  std::vector<int> int_v{1,2,3,2,5};
  std::cout << "acc count: "
            << std::accumulate(int_v.cbegin(), int_v.cend(), 0, counter) << std::endl;
}

//Filter
template<typename T, typename Function>
//decltype(auto) filter(T&& list, Function func) {
  //const_cast<T>(decltype(list)) filtered_list;
decltype(auto) filter1(T collections, Function func) {
  T filtered_collections;
  std::copy_if(collections.cbegin(), collections.cend(),
               std::back_inserter(filtered_collections), func);
  return std::forward<T>(filtered_collections);
}

template<typename T, typename Function>
decltype(auto) filter(T collections, Function func) {
  return std::accumulate(collections.begin(), collections.end(),
                         collections,func);
}
void print_filter() {
  auto persons = getPersons();
  std::vector<Person> filtered_persons;

  auto is_gender1 = [](const Person& person) {
    if(person.gender() == Person::Gender::male)
        return true;
     else
        return false;
    };

  auto is_gender = [](std::vector<Person>& persons, const Person& person2) {
      return persons;
  };

//  std::copy_if(persons.cbegin(),persons.cend(), std::back_inserter(filtered_persons), is_gender);

  std::cout << "males size: " << filtered_persons.size() << std::endl;
  std::cout << "template filter size: " << filter(persons, is_gender).size() << std::endl;
}

//Sort -> ERROR: ㅅㅂ 그냥 cbegin, cend해서 그런거였네
void print_compare_age() {
  auto persons = getPersons();
  greater_person greater_p;
  //std::sort(persons.begin(), persons.end(), greater_p);
  std::sort(persons.begin(), persons.end(),
            [](const Person& person1, const Person& person2) { return person1 < person2; });
  for (auto person : persons) {
    std::cout << "sorted name: " << person.name() <<  ",age: " << person.age() << std::endl;
  }
}

//Sort
void print_sort() {
  std::vector<int> int_v{1,2,6,3,7,2,8};
  std::sort(int_v.begin(), int_v.end(), std::greater<>());
  //std::sort(int_v.begin(), int_v.end(), std::greater<int>());
  for (auto i : int_v) {
    std::cout << "sorted: " << i << std::endl;
  }
}

void print_function() {
  auto persons = getPersons();
  std::vector<Person> filtered_persons;
  std::function<bool(const Person&)> is_gender = [](const Person& person) {
    if(person.gender() == Person::Gender::male)
        return true;
     else
        return false;
    };
  std::copy_if(persons.cbegin(),persons.cend(), std::back_inserter(filtered_persons), is_gender);
}

int main(int argc, char** argv) {
  print_copy();
  print_gender_count();
  print_variable_ramda();
  print_general_ramda_capture();
  print_generic_ramda();
  print_filter();
  print_compare_age();
  print_sort();
  print_function();
  return 0;
}
