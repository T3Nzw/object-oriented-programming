#include <iostream>
#include <fstream>

bool write(char const *filename, int *arr, size_t n) {
  if (!arr)
    return false;

  std::ofstream ofs(filename, std::ios::out);
  if (!ofs.is_open()) {
    return false;
  }

  // 1. ofs.put(char c)
  // 2. operator<< (полиморфен)
  for (size_t i = 0; i < n; ++i) {
    ofs << arr[i] << ' ';
  }

  ofs.close();

  return true;
}

int main() {

  int arr[]{1,2,3};
  write("file2.txt", arr, 3);

  std::cout.put('a').put('b');
  std::cout << 245;

  return 0;
}
