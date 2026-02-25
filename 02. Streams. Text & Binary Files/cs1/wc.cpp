#include <iostream>
#include <fstream>

// задача 03

constexpr unsigned int MAX_SIZE = 129;

struct wc_output {
  size_t bytes;
  size_t words;
  size_t lines;
};

void print(wc_output const &output) {
  std::cout << "Bytes: " << output.bytes << '\n';
  std::cout << "Words: " << output.words << '\n';
  std::cout << "Lines: " << output.lines << '\n';
}

bool isWhitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t';
}

wc_output wc(char const *filename) {
  wc_output result{};

  std::ifstream fin;
  fin.open(filename);
  if (!fin.is_open()) {
    std::cerr << "could not open file " << filename << '\n';
    return result;
  }

  char prev, c;
  if (fin.get(prev)) {

    if (!isWhitespace(prev))
      result.words++;

    result.bytes++;
  }

  while (fin.get(c)) {
    if (c == '\n')
      result.lines++;

    if (isWhitespace(prev) && !isWhitespace(c))
      result.words++;

    result.bytes++;
    prev = c;
  }

  return result;
}

int main() {

  char filename[MAX_SIZE];
  std::cin.getline(filename, MAX_SIZE);

  wc_output output = wc(filename);
  print(output);

  return 0;
}
