#include <iostream>

// идея на наследяването, подтипове
// protected
// атрибути за достъп
// полета/методи с еднакви имена
// г4
// upcasting, downcasting, виртуални методи, статично и динамично свързване

class A {
public:
  A() : x(15) {}

  void print() const {
    std::cout << "A\n";
  }

public:
  int x;
private:
  int y;
protected:
  int z;
};

// public:
// public -> public
// private -> private
// protected -> protected

// private:
// public -> private
// protected -> private
// private -> private

// protected:
// public -> protected
// protected -> protected
// private -> private
class B : public A {
public:
  int s;

  void print() const {
    std::cout << "B\n";
  }

public:
  int x;
};

class E : B {
public:
  int t;
};

struct C {
  int x;
};

struct D : C {};

int main() {

  A a;
  // std::cout << a.x << '\n';
  // a.z;

  B b;
  // std::cout << b.A::x << '\n';
  // b.z;

  // D d;
  // d.x;

  a.print();

  b.A::print();

  return 0;
}
