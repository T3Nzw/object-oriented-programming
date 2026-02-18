#include <iostream>

union ip_address {
  unsigned int addr;
  unsigned char octets[4];
};

int main() {

  ip_address ip;

  ip.octets[0] = 127;
  ip.octets[1] = 0;
  ip.octets[2] = 0;
  ip.octets[3] = 1;

  std::cout << ip.addr << '\n';

  // тук трябва екплиситно да преобразуваме елементите
  // до тип int, тъй като иначе ще изведем символите,
  // на които съотвестват дадените ASCII кодове, на стандарния изход
  for (int i = 0; i < 3; ++i)
    std::cout << static_cast<int>(ip.octets[i]) << '.';

  // fun fact - унарният оператор + се използва именно
  // за преобразуване до int, т.е. е аналогично на горното
  std::cout << +ip.octets[3] << '\n';

  return 0;
}
