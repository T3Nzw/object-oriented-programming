#include <iostream>

class A {
public:
  int x;
private:
  int y;
protected:
  int z;
};

// public inh
// public -> public
// protected -> protected
// private -> private

// protected inh
// public -> protected
// protected -> protected
// private -> private

// private inh
// public -> private
// protected -> private
// private -> private

class B : public A {
public:
  int s;
};

struct C {};

// empty base optimization
struct D {
  int x;
};

int main() {

  std::cout << sizeof(A) << ' ' << sizeof(B) << '\n';
  std::cout << sizeof(C) << ' ' << sizeof(D) << '\n';

  return 0;
}
