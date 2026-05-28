#include <iostream>
#include <vector>
#include <memory>

struct A {
  A(A const &); // копиращ конструктор
  A &operator=(A const &); // копиращ оператор=

  // избягване на излишни копия
  A(A &&other) noexcept; // конструктор за преместване
  A &operator=(A &&) noexcept; // преместващ оператор=
};

int main() {

  int z = 10;
  // lvalue референция
  // value category: lvalue
  int &y = z;

  // rvalue референция
  // t е lvalue
  int &&t = 7;

  // std::move: lvalue -> rvalue
  // reference collapsing
  int &&s = static_cast<int &&>(y);

  // грешка
  // int &&v = z;

  int *arr1;
  int *arr2 = arr1;

  const int x = 10;

  std::vector<std::vector<int> > vec;
  // int ** ~> matrix

  // vec2.matrix = vec.matrix
  // vec.matrix = nullptr

  // няма да използваме vec

  std::vector<std::vector<int> > vec2 = vec;

  // double-free
  // delete[] arr1;
  // delete[] arr2;

  std::unique_ptr<int> uptr = std::make_unique<int>(10);
  // std::unique_ptr<int> uptr2 = uptr;

  int *ptr = new int(10);
  int *ptr2 = ptr;

  // ptr

  delete ptr;

  return 0;
}
