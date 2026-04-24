#include <cstring>
#include <iostream>

// идеално бихме използвали разделна компилация :)
// не се различава съществено от това, което сме писали досега,
// просто е един допълнителен include на базовия клас в заглавния файл

class Employee {
public:
  char const *getName() const {
    return m_name;
  }

  int getId() const {
    return m_id;
  }

  double getSalary() const {
    return m_salary;
  }

  void setName(char const *name) {
    delete[] m_name;
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
  }

  void setId(int id) {
    m_id = id;
  }

  void setSalary(double salary) {
    if (salary < 0)
      return;

    m_salary = salary;
  }

public:
  Employee(char const *name, int id, double salary)
  : m_name(new char[strlen(name) + 1]), m_id(id), m_salary(salary) {
    strcpy(m_name, name);
  }

  Employee(Employee const &other) {
    copy(other);
  }

  Employee(Employee &&other) noexcept {
    move(std::move(other));
  }

  Employee &operator=(Employee const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  Employee &operator=(Employee &&other) noexcept {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~Employee() {
    free();
  }

private:
  void copy(Employee const &other) {
    m_name = new char[strlen(other.m_name) + 1];
    strcpy(m_name, other.m_name);

    m_id = other.m_id;

    m_salary = other.m_salary;
  }

  void move(Employee &&other) noexcept {
    m_name = other.m_name;
    m_id = other.m_id;
    m_salary = other.m_salary;

    other.m_name = nullptr;
    other.m_id = -1;
    other.m_salary = 0;
  }

  void free() {
    delete[] m_name;
  }

private:
  char *m_name;
  int m_id;
  double m_salary;
};

class Manager : public Employee {
public:
  unsigned getTeamSize() const {
    return m_teamSize;
  }

// голямата шестица НЕ се наследява
public:
  // трябва да инициализираме полетата на базовия клас,
  // така че трябва да подадем и стойностите, които приема
  // параметризираният конструктор на Employee
  Manager(char const *name, int id, double salary, unsigned teamSize)
  : Employee(name, id, salary), m_teamSize(teamSize) {}

  // нямаме нужда от останалите методи от г6,
  // тъй като те се създават автоматично (и нямаме динамична памет)
  // и "правилно" викат методите от г6 на "подобекта"
  // от базовия клас (напр. копиращият конструктор на Manager
  // вика копиращия конструктор на Employee)

private:
  // впоследствие ще видим как може да пазим и кои са тези работници :)
  unsigned m_teamSize;
};

class Engineer : public Employee {
public:
  char const *getLanguage() const {
    return m_lang;
  }

  void setLanguage(char const *lang) {
    delete[] m_lang;
    m_lang = new char[strlen(lang) + 1];
    strcpy(m_lang, lang);
  }

public:
  Engineer(char const *name, int id, double salary, char const *lang)
  : Employee(name, id, salary), m_lang(new char[strlen(lang) + 1]) {
    strcpy(m_lang, lang);
  }

  // тук (в този клас) имаме динамична памет, така че
  // трябва да напишем ръчно методите от г6

  // other очевидно е от тип Engineer,
  // но можем да приложим т.нар. upcasting
  // (преобразуваме нещо от тип на производен клас
  // към нещо от тип на базов клас, т.е. "орязваме"
  // обекта от производния клас до такъв на базовия)
  Engineer(Engineer const &other) : Employee(other) {
    copy(other);
  }

  // ако не използваме std::move(other), а само - other,
  // би се извикал копиращият конструктор на Employee
  Engineer(Engineer &&other) noexcept : Employee(std::move(other)) {
    move(std::move(other));
  }

  Engineer &operator=(Engineer const &other) {
    if (this != &other) {
      Employee::operator=(other);
      free();
      copy(other);
    }
    return *this;
  }

  Engineer &operator=(Engineer &&other) noexcept {
    if (this != &other) {
      Employee::operator=(std::move(other));
      free();
      move(std::move(other));
    }
    return *this;
  }

  // не е нужно ръчно да викаме деструктора на базовия клас,
  // това се прави автоматично
  ~Engineer() {
    free();
  }

private:
  void copy(Engineer const &other) {
    m_lang = new char[strlen(other.m_lang) + 1];
    strcpy(m_lang, other.m_lang);
  }

  void move(Engineer &&other) noexcept {
    m_lang = other.m_lang;
    other.m_lang = nullptr;
  }

  void free() {
    delete[] m_lang;
  }

private:
  char *m_lang;
};

int main() {

  Engineer e("engineer", 4, 425.0, "Haskell");
  std::cout << e.getName() << '\n';
  std::cout << e.getSalary() << '\n';
  std::cout << e.getLanguage() << '\n';

  return 0;
}
