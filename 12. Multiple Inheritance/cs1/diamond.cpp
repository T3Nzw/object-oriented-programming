#include <iostream>

struct A {
  int x;

  void foo() const {
    std::cout << "foo\n";
  }

  A(int x) : x(x) {
    std::cout << "A\n";
  }
};

struct B : virtual A {
  void foo() const {
    std::cout << "foo2\n";
  }

  B(int x) : A(x) {}
};

struct C : virtual A {
  void foo() const {
    std::cout << "foo2\n";
  }

  C(int x) : A(x) {
    this->x = 10;
  }
};

struct D : public B, public C {
  D(int t) : A(t+2), C(t-1), B(t) {}
};

int main() {

  A a(10);
  a.foo();

  B b(1);
  b.foo();

  C c(5);
  c.foo();

  D d(5);
  std::cout << d.x;

  return 0;
}
