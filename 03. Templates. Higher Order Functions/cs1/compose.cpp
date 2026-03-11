#include <iostream>
#include <functional>

// задача 03

// <functional> ни предоставя възможността за създаване на
// функционални обекти от тип std::function<тип_на_функция>.
// на практика е по-добре да се използват такива функционални обекти
// вместо "сурови" функционални указатели, тъй като функционалните обекти
// ни позволяват създаването на по-сложни функции, които да прихващат
// някакви стойности от по-външна област (вж. (*) в main)

// f: Dom -> Rng
template<typename Dom, typename Rng>
using Function = Rng(*)(Dom);

// f: A -> B
// g: B -> C
// (g . f): A -> C

// (g . f)(x) := g(f(x))
template<typename A, typename B, typename C>
std::function<C(A)> compose1(Function<B, C> g, Function<A, B> f) {
  // тук функционалните указатели f и g са локални променливи,
  // които не биха били достъпни в ламбда-функцията без capture клауза
  return [f, g](A x) { return g(f(x)); };
}


// по-добре е да използваме std::function навсякъде

template<typename A, typename B, typename C>
std::function<C(A)> compose(std::function<C(B)> const &g, std::function<B(A)> const &f) {
  // можем да запишем типа на връщания резултат по този начин.
  // можехме да го напишем така и в по-горната функция, няма значение дали
  // работим с функционален указател или функционален обект
  return [f, g](A x) -> C { return g(f(x)); };
}

int main() {

  std::cout << std::boolalpha;

  std::function<int(int)> addOne = [](int x) -> int { return x+1; };
  std::function<bool(int)> odd = [](int x) -> bool { return x%2; };

  std::function<bool(int)> oddSucc = compose(odd, addOne);

  // следните извиквания са семантично еквивалентни

  std::cout << odd(addOne(2)) << '\n';
  std::cout << oddSucc(2) << '\n';
  std::cout << compose(odd, addOne)(2) << '\n';


  // прихващане на стойност чрез capture клауза (*)

  int x;
  std::cin >> x;

  // [] се използва именно за прихващане (capture) на променливи
  // от текущата или от по-външна област - иначе това би било невъзможно.
  // така прихващаме x по стойност (т.е. копираме по стойност)
  std::function<int(int)> addX = [x](int y) -> int { return x + y; };


  int y = 11, z = 15;

  // прихващаме всички променливи/константи по стойност
  std::function<int(int)> addXYZ = [=](int t) -> int { return t + x + y + z; };


  // прихващаме y по референция

  std::function<void(void)> modY = [&y]() -> void { y++; };


  // прихващаме всичко по референция

  std::function<void(void)> modAll = [&]() {
    x = y;
    z++;
    y = -1;
  };

  return 0;
}
