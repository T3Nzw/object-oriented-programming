#include <iostream>
#include <fstream>

// задача 02

constexpr unsigned int MAX_SIZE = 129;

void halve(char const *filename) {
  std::ifstream ifile(filename, std::ios::in);
  if (!ifile.is_open()) {
    std::cout << "could not open file\n";
    return;
  }

  ifile.seekg(0, std::ios::end);
  long long mid = ifile.tellg() / 2;

  char *arr = new char[mid+1];

  ifile.seekg(0, std::ios::beg);
  for (long long i = 0; i < mid; ++i) {
    ifile.get(arr[i]);
  }
  arr[mid] = '\0';

  ifile.close();

  // ако файлът не съществува, се създава празен такъв с даденото име;
  // в противен случай съдържанието на съществуващия файл се изтрива
  std::ofstream ofile(filename, std::ios::out);
  if (!ofile.is_open()) {
    delete[] arr;
    std::cout << "could not open file\n";
    return;
  }

  ofile << arr;

  ofile.close();

  delete[] arr;
}

int main() {

  char filename[MAX_SIZE];
  std::cin.getline(filename, MAX_SIZE);

  halve(filename);

  return 0;
}
