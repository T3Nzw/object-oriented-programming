#include <iostream>

enum Season {
  WINTER=1,  // 1
  SPRING=5,  // 5
  SUMMER=2,  // 2
  AUTUMN     // 3
} /*default_season*/;

Season default_season;

enum class Season2 {
  WINTER2,  // 0
  SPRING2,  // 1
  SUMMER2,  // 2
  AUTUMN2   // 3
};

char const *toString(Season season) {
  switch (season) {
    case WINTER: return "winter";
    case SPRING: return "spring";
    case SUMMER: return "summer";
    case AUTUMN: return "autumn";
    default:     return "unknown season";
  }
}

int main() {

  Season season;
  std::cout << default_season << '\n';

  std::cout << sizeof(Season) << '\n';

  std::cout << WINTER << '\n';
  std::cout << static_cast<int>(SPRING) << '\n';
  std::cout << static_cast<int>(SUMMER) << '\n';
  std::cout << static_cast<int>(AUTUMN) << '\n';

  Season s2 = static_cast<Season>(42);

  std::cout << toString(WINTER) << '\n';
  std::cout << toString(s2) << '\n';

  std::cout << static_cast<int>(Season2::WINTER2) << '\n';

  return 0;
}
