#include <iostream>
#include <fstream>

int main() {

  // за четене
  // RAII

  // std::ios::in

  // за двоични файлове - std::ios::binary
  // може да го използваме и за четене, и за писане
  std::ifstream ifs("file.txt", std::ios::in|std::ios::binary);
  if (!ifs.is_open()) {
    std::cout << "could not open file";
    return -1;
  }

  // логика

  ifs.close();

  // за писане
  // std::ios::out
  // ако file.txt не е съществувал, се създава;
  // в противен случай съдържанието се изчиства.

  // ако не искаме да изчистваме съдържанието,
  // използваме std::ios::app или std::ios::ate
  // std::ios::app - премества put указателя в края на файла;
  // винаги когато пишем в този файл, съдържанието се записва в края
  // std::ios::ate - премества put указателя в края на файла,
  // но позволява да бъде преместван
  std::ofstream ofs("file.txt", std::ios::out|std::ios::ate|std::ios::binary);
  if (!ofs.is_open()) {
    return -1;
  }

  // логика

  ofs.close();

  std::cout << 7;

  return 0;
}
