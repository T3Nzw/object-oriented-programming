#ifndef __NOTE_HPP
#define __NOTE_HPP

#include "Entry.hpp"
#include <cstddef>

class Note : public Entry {
public:
  virtual std::size_t size() const override {
    return m_contents.size();
  }

  // Entry -> Note
  // Entry * -> Note *

  virtual Note *clone() const override {
    return new Note(*this);
  }

public:
  Note(std::string const &name, std::string const &contents)
  : Entry(name), m_contents(contents) {}

private:
  std::string m_contents;
};

#endif
