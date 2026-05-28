#include "Directory.hpp"
#include "Entry.hpp"
#include <string>

std::size_t Directory::size() const {
  std::size_t result = 0;

  for (Entry *entry : m_entries) {
    result += entry->size();
  }

  return result;
}

Directory *Directory::clone() const {
  return new Directory(*this);
}

Directory &Directory::addEntry(Entry const &entry) {
  m_entries.push_back(entry.clone());
  return *this;
}

Directory::Directory(std::string const &name)
: Entry(name) {}

Directory::Directory(Directory const &other)
: Entry(other) {
  copy(other);
}

Directory::Directory(Directory &&other) noexcept
: Entry(std::move(other)) {
  move(std::move(other));
}

Directory &Directory::operator=(Directory const &other) {
  if (this != &other) {
    Entry::operator=(other);
    free();
    copy(other);
  }
  return *this;
}

Directory &Directory::operator=(Directory &&other) noexcept {
  if (this != &other) {
    Entry::operator=(std::move(other));
    free();
    move(std::move(other));
  }
  return *this;
}

Directory::~Directory() {
  free();
}

void Directory::copy(Directory const &other) {
  for (Entry *entry : other.m_entries)
    m_entries.push_back(entry->clone());
}

void Directory::move(Directory &&other) noexcept {
  m_entries = std::move(other.m_entries);
}

void Directory::free() {
  for (Entry *entry : m_entries)
    delete entry;

  m_entries.clear();
}
