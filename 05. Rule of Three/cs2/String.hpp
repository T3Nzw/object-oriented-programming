#ifndef __STRING_HPP
#define __STRING_HPP

#include <cstddef>

class String {
public:
  bool empty() const;
  size_t length() const;
  char const *c_str() const;
  void print() const;
  void push_back(char c);
  String &append(String const &other);
  void clear();
  // TODO:
  String slice(size_t start, size_t end) const;
  // s = "abcd123"
  // s.slice(1,4);
  // "bcd1"

public:
  String();
  String(char const *);
  String(String const &);
  String(String &&other) noexcept;
  String &operator=(String const &);
  String &operator=(String &&other) noexcept;
  ~String();

private:
  void copy(String const &);
  void move(String &&other) noexcept;
  void free();
  void resizeTo(size_t newCapacity);

private:
  char *m_str;
  size_t m_size;
  size_t m_capacity;
};

#endif // __STRING_HPP
