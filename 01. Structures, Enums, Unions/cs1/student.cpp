#include <cstring>
#include <iostream>

// заема 148 байта
struct Student {
  char name[129];
  unsigned int age;
  char fn[11];
};

// заема 144 байта
struct Student2 {
  unsigned int age;
  char name[129];
  char fn[11];
};


void print(Student const *s) {
  if (!s) return;

  std::cout << (*s).name << '\n';
  std::cout << s->age  << '\n';
  std::cout << s->fn   << '\n';
}

void print(Student const &s) {
  std::cout << s.name << '\n';
  std::cout << s.age  << '\n';
  std::cout << s.fn   << '\n';
}

int main() {

  Student s1;

  s1.name[0] = 'a';
  s1.name[1] = 'b';
  s1.name[2] = 'c';
  s1.name[3] = '\0';

  strcpy(s1.name, "abc");

  // std::cin.getline(s1.name, 129);

  s1.age = 20;

  int arr[]{1,2,3};

  // Student s2{"alex", 20, "1234567890"};

  // print(s2);

  Student students[100]{};

  std::cout << sizeof(Student) << '\n';
  std::cout << sizeof(Student2) << '\n';

  std::cout << alignof(unsigned) << '\n';

  return 0;
}
