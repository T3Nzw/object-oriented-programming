#include "String.hpp"
#include <cstring>
#include <iostream>

bool String::empty() const {
  return m_size == 0;
}

size_t String::length() const {
  return m_size;
}

char const *String::c_str() const {
  return m_str;
}

void String::print() const {
  std::cout << m_str;
}

void String::push_back(char c) {
  if (m_size+1 >= m_capacity) {
    resizeTo(m_capacity * 2);
  }

  m_str[m_size] = c;
  m_size++;
  m_str[m_size] = '\0';
}

String &String::append(String const &other) {
  if (m_size + other.m_size + 1 >= m_capacity) {
    resizeTo(m_size + other.m_size + 1);
  }

  strcpy(m_str + m_size, other.m_str);
  m_size += other.m_size;

  return *this;
}

void String::clear() {
  m_size = 0;
  m_str[m_size] = '\0';
}

// "abcd" -> {'a', 'b', 'c', 'd', '\0'}
// "" -> {'\0'}

// делегация на конструктори
String::String() : String("") {}

String::String(char const *str) {
  m_size = strlen(str);
  m_capacity = m_size + 1;

  // може да хвърли std::bad_alloc
  m_str = new char[m_capacity];
  strcpy(m_str, str);
}

String::String(String const &other) {
  copy(other);
}

String::String(String &&other) noexcept {
  // other: lvalue (value category)
  // other: String && (type)
  move(std::move(other));
}

String &String::operator=(String const &other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}

String &String::operator=(String &&other) noexcept {
  if (this != &other) {
    free();
    move(std::move(other));
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

void String::move(String &&other) noexcept {
  m_str = other.m_str;
  m_size = other.m_size;
  m_capacity = other.m_capacity;

  // това означава, че move семантиките в нашия случай
  // не са толкова "безплатни" все пак,
  // тъй като пак заделяме памет.
  // тъй като се стремим да запазим other в използваемо
  // състояние и никъде не правим проверки за nullptr
  // в класа, трябва да заделим памет за нов обект
  // по принцип move семантиките имат за цел оптималност,
  // т.е. не бихме искали да правим излишни обекти,
  // така че бихме могли да "релаксираме" инвариантите
  // на класа да се поддържа и nullptr и да се правят проверки
  // и за това
  other = String();

  // обикновено ще искаме нещо такова в линейни
  // последователни контейнери
  // other.m_str = nullptr;
  // other.m_size = 0;
  // other.m_capacity = 0;
}

void String::free() {
  delete[] m_str;
}

// cap: 5
// newCapacity: 3

// pop_back
// strink_to_fit

void String::resizeTo(size_t newCapacity) {
  if (newCapacity <= m_capacity)
    return;

  m_capacity = newCapacity;

  char *newStr = new char[m_capacity];
  strcpy(newStr, m_str);

  delete[] m_str;
  m_str = newStr;
}
