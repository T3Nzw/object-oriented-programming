#include <exception>
#include <iostream>
#include <stdexcept>

class A {
public:
  A() {
    std::cout << "A\n";

    arr = new int[10];

    if (true) {
      delete[] arr;
      throw std::runtime_error("abcd");
    }
  }

  ~A() {
    delete[] arr;
    std::cout << "~A\n";
  }

private:
  int *arr;
};

int main() {

  try {
    A a;
  }
  catch (std::exception const &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
