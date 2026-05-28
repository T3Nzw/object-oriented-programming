#include <iostream>

struct A {
  virtual A *get() {
    std::cout << "A\n";
    return this;
  }
};

// foo(A a) -> foo(B{})
// foo(A *) -> foo(new B{})

// B е подтип на A (B наследява A)
// то B * също е подтип на A *
struct B : A {
  virtual B *get() override {
    std::cout << "B\n";
    return this;
  }

  void foo() const {
    std::cout << "B\n";
  }
};

struct C : A {
  virtual C *get() override {
    std::cout << "C\n";
    return this;
  }
};

int main() {

  A *ptr1 = new B();
  A *ptr2 = new C();

  // static_cast<double>(x), x:int
  // write(reinterpret_cast<char const *>(buf), n)

  // взима указател към обект от тип на базов клас
  // и го преобразува до обект от тип на производен такъв

  // dynamic_cast<B *>(ptr1)

  B *bptr = dynamic_cast<B *>(ptr1);

  if (bptr) {
    bptr->foo();
  }
  else {
    std::cout << "ptr1 was not of type B *\n";
  }

  // ако преобразуванието е възможно,
  // връща указател от тип B *;
  // в противен връща nullptr

  if (dynamic_cast<C *>(ptr1->get())) {
    std::cout << "C *\n";
  }
  else {
    std::cout << "not C *\n";
  }

  return 0;
}
