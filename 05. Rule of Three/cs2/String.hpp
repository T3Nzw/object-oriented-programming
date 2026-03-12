#ifndef __STRING_HPP
#define __STRING_HPP

#include <cstddef>

class String {
public:
  // тук ще напишем останалите методи

public:
  String();
  String(char const *);
  String(String const &);
  String &operator=(String const &);
  ~String();

private:
  void copy(String const &);
  void free();

private:
  char *m_str;
  size_t m_size;
  size_t m_capacity;
};

#endif // __STRING_HPP
