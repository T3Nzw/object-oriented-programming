#include <functional>
#include <ostream>

constexpr unsigned MAX_NAME_SIZE = 101;

class Product {
public:
  int getPrice() const {
    return price;
  }

  unsigned getBarcode() const;

  char const *getName() const;

private:
  unsigned barcode;
  char name[MAX_NAME_SIZE];
  double price;
};

unsigned Product::getBarcode() const {
  return barcode;
}

std::ostream &operator<<(std::ostream &os, Product const &product) {
  os << product.getPrice() << '\n';
  os << product.getName() << '\n';
  return os;
}

class ShoppingCart {
public:
  ShoppingCart &addProduct(Product const &prod) {
    // ...
    return *this;
  }

  void map(std::function<void(Product &)> const &f) {
    for (unsigned i = 0; i < size; ++i)
      f(products[i]);
  }

private:
  Product *products;
  unsigned size;
};

int const foo() {
  return 17;
}

int main() {

  ShoppingCart sc;
  // sc.addProduct(p1).addProduct(p2);

  int *arr = new int[0];

  return 0;
}
