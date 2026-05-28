#include <iostream>
#include <memory>
#include <vector>

struct A {
  virtual void foo() const=0;

  A() : x(0) {
    std::cout << "A()\n";
  }

  A(A const &) {
    std::cout << "A(A const &)\n";
  }

  virtual ~A()=0;

  int x;
};

// ???
A::~A() {}

struct B : A {
  virtual void foo() const override {
    std::cout << "B\n";
  }
};

struct C : A {
  virtual void foo() const override {
    std::cout << "C\n";
  }
};

int main() {

  // (new A{})->foo();

  std::vector<A *> vec;
  vec.push_back(new B());
  vec.push_back(new C());
  vec.push_back(nullptr);
  vec.push_back(new C());

  for (A *ptr : vec) {
    // B C ??? C
    if (!ptr)
      continue;

    ptr->foo();
    // 1, 1, ???, 1
    ptr->x++;
  }

  // как ще преброим броя C-та?

  unsigned cCnt = 0;

  for (A *ptr : vec) {
    if (dynamic_cast<C *>(ptr))
      cCnt++;
  }

  std::cout << cCnt << '\n';

  std::vector<A *> vec2 = vec;

  // 1 -> 2
  vec[3]->x++;

  // 3
  std::cout << ++vec2[3]->x << '\n';

  for (A *ptr : vec) {
    delete ptr;
  }

  std::vector<std::shared_ptr<A> > vec3;

  vec3.push_back(std::make_shared<B>());
  vec3.push_back(std::make_shared<C>());
  vec3.push_back(std::make_shared<C>());

  for (std::shared_ptr<A> const &aptr : vec3)
    aptr->foo();

  return 0;

}
