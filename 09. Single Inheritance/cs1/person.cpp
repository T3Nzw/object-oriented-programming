#include <cassert>
#include <iostream>
#include <string>
#include <cstring>

// идеално бихме използвали разделна компилация

class Person {
public:
  std::string const &getName() const {
    return m_name;
  }

  char const *getEmail() const {
    return m_email;
  }

  unsigned getAge() const {
    return m_age;
  }

public:
  Person(char const *name, char const *email, unsigned age)
  : m_name(name), m_email(new char[strlen(email) + 1]), m_age(age) {
    strcpy(m_email, email);
  }

  Person(Person const &other) {
    copy(other);
  }

  Person &operator=(Person const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

private:
  void copy(Person const &other) {
    m_email = new char[strlen(other.m_email) + 1];
    strcpy(m_email, other.m_email);

    m_age = other.m_age;

    m_name = other.m_name;
  }

  void free() {
    delete[] m_email;
  }

private:
  std::string m_name;
  char *m_email;
  unsigned m_age;
};

class Student : public Person {
public:
  char const *getFn() const {
    return m_fn;
  }

public:
  Student(char const *name, char const *email, unsigned age, char const *fn)
  : Person(name, email, age) {
    assert(strlen(fn) <= 10);
    strcpy(m_fn, fn);
  }

private:
  char m_fn[11];
};

class Teacher : public Person {
public:
  unsigned totalSubjects() const {
    return m_size;
  }

  char const *const *getSubjects() const {
    return m_subjects;
  }

  char const *getSubjectAt(unsigned index) const {
    return m_subjects[index];
  }

public:
  Teacher(char const *name, char const *email, unsigned age, char const *const *subjects, unsigned size)
  : Person(name, email, age), m_size(size) {
    m_subjects = new char*[size];
    for (unsigned i = 0; i < size; ++i) {
      m_subjects[i] = new char[strlen(subjects[i]) + 1];
      strcpy(m_subjects[i], subjects[i]);
    }
  }

  Teacher(Teacher const &other) : Person(other) {
    copy(other);
  }

  Teacher &operator=(Teacher const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

private:
  void copy(Teacher const &other) {
    m_subjects = new char*[other.m_size];
    for (unsigned i = 0; i < other.m_size; ++i) {
      m_subjects[i] = new char[strlen(other.m_subjects[i]) + 1];
      strcpy(m_subjects[i], other.m_subjects[i]);
    }

    m_size = other.m_size;
  }

  void free() {
    for (unsigned i = 0; i < m_size; ++i) {
      delete[] m_subjects[i];
    }
    delete[] m_subjects;
  }

private:
  char **m_subjects;
  unsigned m_size;
};

int main() {

  Person p("name", "email", 20);
  std::cout << p.getAge() << '\n';

  Student s("alex", "email2", 21, "12345");
  std::cout << s.getName() << '\n';
  std::cout << s.getAge() << '\n';
  std::cout << s.getEmail() << '\n';
  std::cout << s.getFn() << '\n';

  char const *subjects[] = {"geometry", "statistics", "functional programming"};

  Teacher t("uchitel", "uchitel@fmi.com", 40, subjects, sizeof(subjects)/sizeof(char const *));
  std::cout << t.getName() << " teaches:\n";
  for (unsigned i = 0; i < t.totalSubjects(); ++i) {
    std::cout << i+1 << ". " <<  t.getSubjectAt(i) << '\n';
  }

  return 0;
}
