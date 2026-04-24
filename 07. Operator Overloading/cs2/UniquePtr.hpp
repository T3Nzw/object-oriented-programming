#ifndef __UNIQUE_PTR_HPP
#define __UNIQUE_PTR_HPP

#include <utility>

// по-надолу използвам термина "притежание" (ownership),
// което, накратко казано, означава следното:
// един обект/област притежава ресурс (напр. динамично заделена памет,
// файлов поток и др.), ако е отговорен за създаването и унищожаването
// на този ресурс (напр. конструктори-деструктор при обекти,
// отваряне-затваряне на файлов поток при работа с файлове и др.).
// в общия случай бихме искали създаването и унищожаването
// на някакъв ресурс да се извършват от един и същи обект/област
// (това е в основата на Resource Acquisition Is Initialization (RAII) принципа).
// за повече информация:
// ownership: https://www.reddit.com/r/cpp_questions/comments/1bd3wgk/what_does_the_term_ownership_mean/
// RAII: https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii

// искаме да симулираме функционалностите на суров (raw) указател,
// като обаче спазваме RAII принципа - т.е. обектите от тип UniquePtr<T>
// сами да се грижат за паметта си (освобождават паметта за нещото от тип T
// в деструктора си). искаме този указател да бъде "уникален", т.е. да не може
// множество указатели (UniquePtr<T>) да сочат към един и същи обект
// (разбира се, както с всичко в C++, можем да bypass-нем и това, но приемаме, че няма :D),
// т.е. да не можем да правим нещо от следния вид, изразено чрез сурови указатели:

// тук и ptr1, и ptr2 сочат към един и същи обект
// T *ptr1 = new T(...);
// T *ptr2 = ptr1;

// очевидно горното би било проблем, понеже лесно можем да "забравим",
// че имаме такова споделяне на памет, и да кажем следното:

// delete ptr1;
// delete ptr2;

// което е double-free (води до недефинирано поведение).
// затова в нашия клас ще искаме да забраним следното:

// UniquePtr<T> ptr1(new T(...));  ~> тук "отдаваме" притежанието на new T(...) на обекта ptr1
// UniquePtr<T> ptr2 = ptr1;

// тоест, ще искаме да забраним копиращите семантики (да изтрием копиращите конструктор и оператор=).
// иначе бихме имали следния проблем:

/*

{
  UniquePtr<T> ptr1 = new T(...);
  UniquePtr<T> ptr2 = ptr1;

  // тук се викат деструкторите на ptr1 и ptr2, които
  // викат delete върху един и същи указател (подобно на горното при сурови указатели),
  // което означава double-free -> недефинирано поведение
}

*/

// ще работим с единични обекти, т.е. няма да имаме масиви с елементи от тип T
template<typename T>
class UniquePtr {
public:
  T &operator*() {
    return *m_ptr;
  }

  T const &operator*() const {
    return *m_ptr;
  }

  // A *a;
  // a->foo();
  // UniquePtr<A> aptr = new A(...);
  // aptr->foo();
  T *operator->() {
    return m_ptr;
  }

  T const *operator->() const {
    return m_ptr;
  }

  // отдаваме притежанието на m_ptr на "външния свят"
  T *release() {
    T *cpy = m_ptr;
    m_ptr = nullptr;
    return cpy;
  }

public:
  UniquePtr() : m_ptr(nullptr) {}

  // в std::unique_ptr<T> (дефиниран в <memory>)
  // няма такъв конструктор и се използва външна функция
  // std::make_unique<T>(data) (вж. по-надолу)
  UniquePtr(T const &data) : m_ptr(new T(data)) {}

  // правим shallow копие;
  // отдаваме притежанието на ptr (нещо от външния свят)
  // на обект от тип UniquePtr<T>
  UniquePtr(T *ptr) : m_ptr(ptr) {}

  // изтриваме автоматично създадения копиращ конструктор
  UniquePtr(UniquePtr const &)=delete;

  // има смисъл да имаме move семантики, тъй като те са
  // вид преместване на притежанието от един обект на друг такъв
  UniquePtr(UniquePtr &&other) {
    move(std::move(other));
  }

  UniquePtr &operator=(UniquePtr const &)=delete;

  UniquePtr &operator=(UniquePtr &&other) {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~UniquePtr() {
    free();
  }

private:
  void move(UniquePtr &&other) {
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
  }

  void free() {
    delete m_ptr;
  }

private:
  T *m_ptr;
};

template<typename T>
UniquePtr<T> makeUnique(T const &data) {
  return UniquePtr<T>(new T(data));
}

#endif // __UNIQUE_PTR_HPP
