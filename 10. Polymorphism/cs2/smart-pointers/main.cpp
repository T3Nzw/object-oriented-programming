#include <iostream>
#include "SharedPtr.hpp"
#include "WeakPtr.hpp"

int main() {

  WeakPtr<int> wp;
  SharedPtr<int> sp1;

  std::cout << "Shared refs: " << wp.getSharedRefs() << '\n';
  std::cout << "Weak refs:   " << wp.getWeakRefs() << '\n';

  {
    SharedPtr<int> sp(15);
    wp = sp;

    std::cout << "Shared refs: " << wp.getSharedRefs() << '\n';
    std::cout << "Weak refs:   " << wp.getWeakRefs() << '\n';

    std::cout << "value: " << *sp << ' ' << *wp << '\n';

    sp1 = sp;

    std::cout << "Shared refs: " << wp.getSharedRefs() << '\n';
    std::cout << "Weak refs:   " << wp.getWeakRefs() << '\n';
  }

  std::cout << "Shared refs: " << wp.getSharedRefs() << '\n';
  std::cout << "Weak refs:   " << wp.getWeakRefs() << '\n';

  if (wp.valid())
    std::cout << "value: " << *wp << '\n';
  else
    std::cout << "invalid weak pointer\n";

  sp1 = SharedPtr<int>(15);

  std::cout << "Shared refs: " << wp.getSharedRefs() << '\n';
  std::cout << "Weak refs:   " << wp.getWeakRefs() << '\n';

  if (wp.valid())
    std::cout << "value: " << *wp << '\n';
  std::cout << "invalid weak pointer\n";

  std::cout << "--------------------------------------\n";

  std::cout << "Shared refs: " << sp1.getSharedRefs() << '\n';
  std::cout << "Weak refs:   " << sp1.getWeakRefs() << '\n';

  WeakPtr<int> wp2 = sp1;

  std::cout << "Shared refs: " << sp1.getSharedRefs() << '\n';
  std::cout << "Weak refs:   " << sp1.getWeakRefs() << '\n';

  return 0;
}
