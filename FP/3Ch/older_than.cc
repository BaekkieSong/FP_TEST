#include <iostream>
#include <typeinfo>   //typeid
#include <functional> //std::function

#include <vector>
#include <numeric> //std::accumulate
#include <string>
#include <algorithm> //std::count_if

class Age {
  public:
    Age(int age) : age_(age) {}
    virtual ~Age() = default;
  protected:
    int age_;
};
class AgeObject : public Age {
  public:
    AgeObject(int age) : Age(age) {}
    virtual ~AgeObject() = default;
    int age() { return age_; }
};
class Person : public AgeObject {
  public:
    enum Gender {
      female,
      male,
      other,
    };
    Person(const std::string& name="사람", const int& age=0, const Gender& gender=other)
      : name_(name),
        AgeObject(age),
        gender_(gender) {}
    virtual ~Person() = default;

    Gender gender() { return gender_; }
  private:
    Gender gender_;
    std::string name_;
};

std::vector<Person> getPersons() {
  std::vector<Person> persons;
  persons.push_back(Person());
  persons.push_back(Person("사람1",30,Person::Gender::female));
  persons.push_back(Person("사람2",45,Person::Gender::male));
  return persons;
}

//일반 함수
bool older_than_42(Person person) {
  return person.age() > 42;
}
//3.1.3 함수 객체 - 연산자 오버로딩
class func_older_than {
  public:
    func_older_than(int age) : age_(age) {}
    bool operator()(Person person) {
      return person.age() > age_;
    }
  private:
    int age_;
};
//3.1.4 일반 함수 객체
template<typename T>
class template_older_than {
  public:
    template_older_than(int age) : age_(age){}
//    bool operator()(const T& t) const {
//      return t.age() > age_;
//    }
    bool operator()(T& t) {
      return t.age() > age_; //컴파일 시점에 검사
    }
  private:
    int age_;
};
// 더 일반적인 객체
class older_than {
  public:
    older_than(int age) : age_(age) {}
//    template<typename T>
//    bool operator()(T&& t) const {
//      return std::forward<T>(t).age() > age_;
//    }
    template<typename T>
    bool operator()(T&& t) {
      return std::forward<T>(t).age() > age_;
    }
  private:
    int age_;
};
void print_older_than() {
  //auto& persons = getPersons(); // 임시객체를 auto&로 받지마라
  auto persons = getPersons();
  std::cout << count_if(persons.cbegin(), persons.cend(), older_than_42) << std::endl;

  func_older_than ot_25(25);
  func_older_than ot_40(40);
  std::cout << count_if(persons.cbegin(), persons.cend(), ot_25) << std::endl;
  std::cout << count_if(persons.cbegin(), persons.cend(), ot_40) << std::endl;

  template_older_than<Person> person_ot_25(25);
  template_older_than<Person> person_ot_40(40);
  std::cout << count_if(persons.begin(), persons.end(), template_older_than<Person>(25)) << std::endl;
  std::cout << count_if(persons.begin(), persons.end(), person_ot_40) << std::endl;
  //Comment 얘 왜 안되냐...? 예제로 나온앤데;;;;
//  std::cout << count_if(persons.cbegin(), persons.cend(), template_older_than<Person>(25)) << std::endl;

  older_than predicate(25);
  std::cout << count_if(persons.begin(), persons.end(), predicate) << std::endl;
  //Comment 얘도 안됨 잦가틈
  //std::cout << count_if(persons.cbegin(), persons.cend(), predicate) << std::endl;
}

int main(int argc, char** argv) {
  print_older_than();
  return 0;
}
