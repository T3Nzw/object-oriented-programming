#include <iostream>

void foo(int *ptr) {
  if (!ptr) return;

  (*ptr)++;
}

void foo(int &x) {
  x++;
}

int main() {

  int x = 4;
  foo(x);

  // 5
  std::cout << x << '\n';

  return 0;
}
