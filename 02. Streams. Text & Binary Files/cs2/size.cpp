#include <ios>
#include <iostream>
#include <fstream>

std::streamsize size(char const *filename) {
  std::ifstream ifs;
  ifs.open(filename, std::ios::in);
  if (!ifs.is_open()) {
    return -1;
  }

  // логика за дължината
  // seekg, tellg
  // seekg(int offset, position)
  // position - std::ios::beg, std::ios::cur, std::ios::end
  // ifs.seekg(10, std::ios::beg);
  // ifs.tellg() - позицията на get указателя

  // изместване наляво от началото на файл???

  ifs.seekg(0, std::ios::end);
  std::streamsize n = ifs.tellg();

  ifs.close();

  return n;
}

std::streamsize size2(char const *filename) {
  // get указателят винаги е в началото на файла
  std::ifstream ifs(filename, std::ios::in);
  if (!ifs.is_open()) {
    return -1;
  }

  // std::istream &get(char &c)
  // 1. int ch = ifs.get(); ifs.get(char &c); - чете само по 1 символ
  // 2. getline(char *buf, size_t n, char delim);
  // 3. operator>> - пропуска символи като ' ', '\t', '\n'
  std::streamsize n = 0;
  // std::ios::goodbit, std::ios::badbit, std::ios::failbit, std::ios::eofbit
  // ifs.good(); ifs.bad(); ifs.fail(); ifs.eof();

  char c;
  // 1. не използваме 1.ifs.eof()
  // 2. не използваме ifs.get() (връща int) в цикли!!!
  while (ifs.get(c)) {
    n++;
  }

  ifs.close();

  return n;
}

int main() {

  std::cout << size2("file.txt") << '\n';

  return 0;
}
