#include <iostream>
#include <vector>

struct A {
  void foo() {
    std::cout << "A\n";
  }

  virtual void bar() {
    std::cout << "A\n";
  }

  // ако имаме поне един чисто виртуален метод,
  // класът е абстрактен => няма как да създаваме
  // обекти от този тип
  virtual void baz() const=0;
};

struct B : A {
  void foo() {
    std::cout << "B\n";
  }

  virtual void bar() override {
    std::cout << "B\n";
  }

  virtual void baz() const override {
    std::cout << "B:baz()\n";
  }
};

class Printable {
public:
  virtual void print() const=0;
};

class Person : public Printable {
public:
  virtual void print() const {
    std::cout << name;
  }

private:
  std::string name="abcd";
};

class Dog : public Printable {
public:
  virtual void print() const {
    std::cout << "this is a dog\n";
  }
};

class C {};

// 12 <= 16
// 1 + 8 <= 8
// sizeof(C) + size(vtable *) <= sizeof(D)

class D : public C {
public:
  virtual void foo() {}
};

void foo(C c) {
}

int main() {

  D d;
  foo(d);

  std::cout << sizeof(C) << '\n';
  // empty-base optimisation
  std::cout << sizeof(D) << '\n'; // 8

  std::vector<Printable *> vec;
  vec.push_back(new Dog{});
  vec.push_back(new Person{});

  for (Printable *ptr : vec) {
    ptr->print();
  }

  A *a;
  B b;

  // статично свързване
  // фунцкията, която се извика, се определя по време на компилация
  a->A::foo(); // A
  b.B::foo(); // B

  A *ptr = a;  // A* <- A*
  A *ptr2 = &b; // A* <- B*

  // динамично свързване
  // фунцкията, която се извиква, се определя по време на изпълнение на програмата
  ptr->bar(); // A
  ptr2->bar(); // B

  return 0;
}
