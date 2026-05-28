#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class Printable {
public:
  virtual void print() const=0;
};

class Serializable {
public:
  virtual void serialize(std::ostream &os) const=0;
};

class Person : public Printable, public Serializable {
public:
  Person(std::string name) : name(name) {}

  virtual void print() const {
    std::cout << name;
  }

  virtual void serialize(std::ostream &os) const {
    os << name;
  }

private:
  std::string name;
};

class Armadillo : public Printable {
public:
  virtual void print() const override {
    std::cout << "gender: " << gender;
  }

private:
  int gender;
};

class A {
public:
  A(int) {
    std::cout << "A\n";
  }
};

class B {
public:
  B() {
    std::cout << "B\n";
  }
};

class C : public A, public B {
public:
  C() : A(5), B() {}

private:
  int x;
  int y;
  int z;
};

int main() {

  std::vector<std::unique_ptr<Printable> > printable;

  printable.push_back(std::make_unique<Person>("person"));
  printable.push_back(std::make_unique<Armadillo>());

  for (std::unique_ptr<Printable> const &ptr : printable) {
    ptr->print();
  }

  C c;


  return 0;
}
