#include <iostream>
#include "UniquePtr.hpp"

int main() {

  UniquePtr<int> uptr;
  UniquePtr<int> uptr2 = std::move(uptr);

  int *ptr = uptr.release();

  return 0;
}
