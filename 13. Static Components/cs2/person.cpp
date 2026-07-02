#include <iostream>
#include <string>

class Person {
public:
  Person(std::string name, unsigned char age)
  : name(name), age(age), id(idCnt++) {}

  Person(Person &&other) noexcept
  : name(std::move(other.name)), age(other.age), id(other.id) {
    other.age = 0;
    other.id = -1;
  }

  std::string const &getName() const {
    return name;
  }

  unsigned char getAge() const {
    return age;
  }

private:
  std::string name;
  unsigned char age;
  int id;

  static int idCnt;
};

int Person::idCnt = 0;

int main() {

  Person p1("name1", 21); // id: 1

  {
    Person p2("name2", 21); // id: 2, idCnt: 3
  } // idCnt-- => idCnt: 2

  Person p3("name3", 21); // id: 2

  Person p4 = Person(p3.getName(), p3.getAge());

  return 0;
}
