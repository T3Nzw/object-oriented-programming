#include <iostream>
#include <fstream>

// задача 01

constexpr unsigned int MAX_SIZE = 129;

void print(char const *filename) {
  std::ifstream ifile;
  ifile.open(filename, std::ios::in);

  if (!ifile.is_open()) {
    std::cout << "could not open file\n";
    return;
  }

  char c;
  while (ifile.get(c)) {
    std::cout << c;
  }

  ifile.close();
}

int main() {

  char filename[MAX_SIZE];
  std::cin.getline(filename, MAX_SIZE);

  print(filename);

  return 0;
}
