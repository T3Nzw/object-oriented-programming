#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "SinglyLinkedList.hpp"
#include <forward_list>

// TODO:
// 1. maximum (maximum_by)
// 2. find
// 3. find_if
// 4. sort
// 5. transform
// 6. partition

// [begin,end)
template<typename iterator_type>
iterator_type maximum(iterator_type begin, iterator_type end) {
  iterator_type result = begin;

  while (begin != end) {
    if (*begin > *result)
      result = begin;

    ++begin;
  }

  return result;
}

// forward iterators
template<typename iterator_type, typename T>
iterator_type find(iterator_type begin, iterator_type end, T const &value) {

  while (begin != end) {
    if (*begin == value)
      return begin;

    ++begin;
  }

  return begin;
}

// template<typename iterator_type, typename T>
// iterator_type find_if(iterator_type begin, iterator_type end, std::function<bool(T const &)> const &p) {
  // while (begin != end) {
    // if (p(*begin))
      // return begin;

    // ++begin;
  // }

  // return begin;
// }

template<typename iterator_type, typename Pred>
iterator_type find_if2(iterator_type begin, iterator_type end, Pred p) {
  while (begin != end) {
    if (p(*begin))
      return begin;

    ++begin;
  }

  return begin;
}

template<typename input_iterator_type, typename output_iterator_type, typename F>
output_iterator_type transform(input_iterator_type begin, input_iterator_type end, output_iterator_type result, F f) {

  while (begin != end) {
    // result[j] = f(arr[i]);
    *result = f(*begin);
    ++begin;
    ++result;
  }

  return result;
}

int main() {

  std::vector<int> v = {1,2,3};

  // iterator??
  // begin, end - за контейнера
  // за итератор:
  // operator++
  // operator!=
  // operator* - *it
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ' ';
  }

  // --

  for (int el : v) {
    std::cout << el << ' ';
  }

  Vector<int> const v2;

  for (Vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
  }

  // [1,2,3,4,5,6]

  for (int el : v2)
    std::cout << el << ' ';

  std::forward_list<int> l;
  for (int el : l) {
  }

  LinkedList<int> ll;
  ll.push_back(5);
  ll.push_back(6);

  for (int el : ll) {
    std::cout << el << ' ';
  }

  Vector<int> v3;
  // std::cout << *maximum(v2.begin(), v2.end());

  std::cout << *maximum(v.begin(), v.end());

  std::cout << '\n';

  // std::cout << *find_if<std::vector<int>::iterator, int>(v.begin(), v.end(), [](int const &x) -> bool { return x % 2 == 0; });
  // std::vector<int>::iterator ~> std::vector<char>::iterator

  std::cout << '\n';

  std::cout << *find_if2(v.begin(), v.end(), [](int x) -> bool { return x % 2 == 0; });

  std::vector<char> result(v.size());
  transform(v.begin(), v.end(), result.begin(), [](int x) -> char { return x + '0'; });

  for (char el : result)
    std::cout << el << ' ';
}
