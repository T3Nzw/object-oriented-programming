#include <iostream>

class Singleton {
public:
  static Singleton *getInstance() {
    if (!instance)
      instance = new Singleton();
    return instance;
  }

public:
  Singleton(Singleton const &)=delete;
  Singleton(Singleton &&) noexcept=delete;
  Singleton &operator=(Singleton const &)=delete;
  Singleton &operator=(Singleton &&) noexcept=delete;

private:
  Singleton()=default;

private:
  static Singleton *instance;
};

Singleton *Singleton::instance = nullptr;

class SingletonRef {
public:
  static SingletonRef &getInstance() {
    static SingletonRef instance;
    return instance;
  }

public:
  SingletonRef(SingletonRef const &)=delete;
  SingletonRef(SingletonRef &&) noexcept=delete;
  SingletonRef &operator=(SingletonRef const &)=delete;
  SingletonRef &operator=(SingletonRef &&) noexcept=delete;

private:
  SingletonRef()=default;
};

int main() {

  Singleton *s1 = Singleton::getInstance();
  Singleton *s2 = Singleton::getInstance();

  SingletonRef &sref = SingletonRef::getInstance();

  return 0;
}
