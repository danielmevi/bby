/* Daniel Medina Villegas
 *
 * Template metaprogramming
 *
 * Fibonacci puzzle
 * This is old implementation of metaprogramming code to implement compilation
 * computation.
 * This code it is meant to calculate the fibnacci of any long number
 *
 */

#include <iostream>

///////////////////////////////////////////////////////////
template <unsigned n> struct fibonacci {
  enum { value = fibonacci<n - 1>::value + fibonacci<n - 2>::value };
};
template <> struct fibonacci<1> {
  enum { value = 1 };
};
template <> struct fibonacci<0> {
  enum { value = 1 };
};
////////////////////////////////////////////////////////////

int main() {
  std::cout << fibonacci<4>::value << std::endl;

  return 1;
}
