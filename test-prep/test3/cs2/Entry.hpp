#ifndef __ENTRY_HPP
#define __ENTRY_HPP

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>

class Entry {
public:
  virtual std::size_t size() const=0;

  std::string const &name() const {
    return m_name;
  }

  virtual Entry *clone() const=0;

public:
  Entry(std::string const &name) {
    // ' ', '\t', '\n'

    for (char c : name) {
      if (!std::islower(c) && !isBlank(c))
        throw std::runtime_error("name is invalid");
    }

    m_name = name;
  }

  virtual ~Entry()=default;

private:
  static bool isBlank(char c) {
    return c == ' ' || c == '\t' || c == '\n';
  }

private:
  std::string m_name;
};

#endif
