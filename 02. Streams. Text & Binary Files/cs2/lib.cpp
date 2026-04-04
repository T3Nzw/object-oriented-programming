#include <ios>
#include <iostream>
#include <fstream>

constexpr unsigned MAX_LIBRARY_SIZE = 128;

enum class Genre {
  FANTASY, CLASSICAL
};

char const *toString(Genre g) {
  switch (g) {
    case Genre::CLASSICAL: return "classical";
    case Genre::FANTASY:   return "fantasy";
  }

  return "unknown genre";
}

struct Book {
  char title[64];
  char author[32];
  unsigned pages;
  Genre genre;

  void print() const {
    std::cout << title << '\n';
    std::cout << author << '\n';
    std::cout << pages << '\n';
    std::cout << toString(genre) << '\n';
  }
};

struct Library {
  Book books[MAX_LIBRARY_SIZE];
  unsigned currSize;
};

void writeBook(std::ofstream &ofs, Book const &book) {
  if (!ofs)
    return;

  ofs.write(reinterpret_cast<char const *>(&book), sizeof(book));
}

void writeLibrary(char const *filename, Library const &library) {
  std::ofstream ofs(filename, std::ios::out|std::ios::binary);
  if (!ofs)
    return;

  ofs.write(reinterpret_cast<char const *>(library.books),sizeof(Book) * library.currSize);

  // for (unsigned i = 0; i < library.currSize; ++i) {
    // writeBook(ofs, library.books[i]);
  // }

  ofs.close();
}

void readLibrary(char const *filename, Library &library) {
  std::ifstream ifs(filename, std::ios::in|std::ios::binary);
  if (!ifs)
    return;

  ifs.seekg(0, std::ios::end);
  std::streamsize size = ifs.tellg();

  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char *>(library.books), size);

  library.currSize = size / sizeof(Book);
}

int main() {

  Book b1{"Harry Potter", "J. K. Rowling", 400, Genre::FANTASY};
  Book b2{"The Little Prince", "Anton", 100, Genre::CLASSICAL};

  Library lib;
  lib.books[0] = b1;
  lib.books[1] = b2;

  lib.currSize = 2;

  writeLibrary("lib.bin", lib);

  Library lib2;
  readLibrary("lib.bin", lib2);

  for (unsigned i = 0; i < lib2.currSize; ++i) {
    lib2.books[i].print();
  }

  return 0;
}
