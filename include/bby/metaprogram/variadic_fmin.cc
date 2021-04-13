/*
 *
 */

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>

// C++17 Fold-Expression
// template <typename First, typename ... T>
// decltype(auto) variadic_fmin(const First& f, const T& ... t) {
//    First retval = f;
//    std::initializer_list<First>{(retval = std::fmin(retval, t))...};
//    return retval;
//}

// C++17
// template <typename First, typename ... T>
// First variadic_fmin(const First& f, const T& ... t) {
//    const First* retval = &f;
//    ((retval = std::fmin(retval, t))...);
//    return *retval;
//}

// C++11
template <typename First, typename... T>
First variadic_fmin(const First &f, const T &... t) {
  First retval = f;
  std::initializer_list<First> list{(retval = std::fmin(retval, t))...};
  return *list.begin();
}

int my_min(int x, int y, int z) { return std::min({x, y, z}); }

int main(const int, const char *const[]) {
  std::cout << std::min(1, 2) << '\n';
  std::cout << my_min(1, 2, 3) << '\n';
  std::cout << variadic_fmin(-1.3f, NAN, NAN, NAN, 3.0f, 0) << '\n';

  return 1;
}
