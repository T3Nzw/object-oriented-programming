#include "String.hpp"
#include <cstring>

String::String() : m_size(0), m_capacity(1) {
  m_str = new char[m_capacity];
  m_str[0] = '\0';
}

String::String(char const *str) {
  m_size = strlen(str);
  m_capacity = m_size + 1;

  m_str = new char[m_capacity];
  strcpy(m_str, str);
}

String::String(String const &other) {
  copy(other);
}

String &String::operator=(String const &other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}

String::~String() { free(); }

void String::copy(String const &other) {
  m_size = other.m_size;
  m_capacity = other.m_capacity;

  m_str = new char[m_capacity];
  strcpy(m_str, other.m_str);
}

void String::free() {
  delete[] m_str;
}
