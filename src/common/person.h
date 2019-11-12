#ifndef __PERSON__
#define __PERSON__

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
    int age() const { return age_; }
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

    bool operator<(const Person& person) const {
      return this->age_ < person.age();
    }
    bool operator>(const Person& person) const {
      return this->age_ > person.age();
    }
    bool operator==(const Person& person) const {
      return this->age_ == person.age();
    }
//
//    Person& operator=(const Person& person) {
//      age_ = person.age();
//      name_ = person.name();
//      gender_ = person.gender();
//      return *this;
//    }

    Gender gender() const { return gender_; }
    std::string name() const { return name_; }
  private:
    Gender gender_;
    std::string name_;
};

//
class greater_person {
  public:
    bool operator()(const Person& person1, const Person& person2) const {
      return person1.age() < person2.age();
    }
};

std::vector<Person> getPersons() {
  std::vector<Person> persons;
  persons.push_back(Person("사람1",36,Person::Gender::female));
  persons.push_back(Person("사람2",44,Person::Gender::male));
  persons.push_back(Person("사람3",21,Person::Gender::male));
  persons.push_back(Person("사람4",41,Person::Gender::male));
  persons.push_back(Person("사람5",27,Person::Gender::female));
  persons.push_back(Person("사람6",25,Person::Gender::male));
  persons.push_back(Person("사람7",33,Person::Gender::female));
  persons.push_back(Person("사람8",49,Person::Gender::male));
  return persons;
}


//class ramda_impl;  //ERROR: Not Work

//==[&gender](const Person& person){ return person.gender() == gender; }
class ramda_gender {
  public:
    ramda_gender(const Person::Gender& gender) : gender_(gender) {}
    bool operator()(const Person& person) {
      return person.gender() == gender_;
    }
  private:
    const Person::Gender& gender_;
};

class GenderGroup {
  public:
    GenderGroup(const std::vector<Person>& persons) : persons_(persons) {}
    int getNumGenders(const Person::Gender& gender) {
      return count_if(persons_.cbegin(),persons_.cend(),
                          ramda_gender(gender));
//                        [gender](const Person& person){
//                          return person.gender() == gender;
//                        });
    }

    std::vector<Person> return_same_gender_persons(const Person::Gender& gender) {
      std::vector<Person> persons;
      std::copy_if(persons_.cbegin(), persons_.cend(), std::back_inserter(persons),
                    [this, &gender](const Person& person) {
                      return person.gender() == gender;
                    });
      return persons;
    }

    const Person::Gender gender_for_person(const Person& person) const {
      return person.gender();
    }
    int count_same_gender_persons(const Person::Gender& gender) {
      return std::count_if(persons_.cbegin(), persons_.cend(),
                            [this, &gender](const Person& person) {
                              return gender_for_person(person) == gender;
                            });
    }

  private:
    std::vector<Person> persons_;
};

//ramda to closure with class method
//void GenderGroup::count_same(const Person::Gender& gender) {
// == [this, &gender](const Person& person){ return person.age() == this.age(); }
//}
class ramda_impl {
  public:
    ramda_impl(const GenderGroup* arg1, const Person::Gender& arg2) : arg1_(arg1), arg2_(arg2) {
    }
    bool operator()(const Person& person) const {
      return arg1_->gender_for_person(person) == arg2_;
    }
  private:
    const GenderGroup* arg1_;
    const Person::Gender& arg2_;

};

#endif
