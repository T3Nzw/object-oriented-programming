#ifndef __DIRECTORY_HPP
#define __DIRECTORY_HPP

#include "Entry.hpp"
#include <cstddef>
#include <vector>

class Directory : public Entry {
public:
  virtual std::size_t size() const override;

  // Directory d;
  // d.addEntry(...).addEntry(...);

  virtual Directory *clone() const override;

  Directory &addEntry(Entry const &entry);

public:
  Directory(std::string const &name);
  Directory(Directory const &other);
  Directory(Directory &&other) noexcept;
  Directory &operator=(Directory const &other);
  Directory &operator=(Directory &&other) noexcept;
  virtual ~Directory() override;

private:
  void copy(Directory const &other);
  void move(Directory &&other) noexcept;
  void free();

private:
  std::vector<Entry *> m_entries;
};

#endif
