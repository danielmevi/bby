/* Daniel Medina Villegas
 *
 * Template metaprogramming
 *
 * binary 2 decimal converter
 * This is moder metaprogramming code, inheritates from C++14 libraries and
 * techniques
 * The code it is meant to parse any long 1,0's as binaries to decimal
 *
 */

#include <iostream>
#include <type_traits>

using namespace std;

/* TMP code to generate conversion from binary format to decimal */
//////////////////////////////////////////////////////////////////
template <unsigned T>
struct binary_parser
    : integral_constant<unsigned, (T % 10) + 2 * binary_parser<T / 10>::value> {
};
template <> struct binary_parser<0> : integral_constant<unsigned, 0> {};
//////////////////////////////////////////////////////////////////
template <typename T, T n> struct integral_constant_2 {
  static constexpr auto status = n;
};
template <unsigned T>
struct bins : integral_constant_2<bool, bins<T / 10>::status> {
  static_assert(
      (T % 10) < 2,
      "ERROR: binary<X>::value template only accepts 1,0's integral values");
};
template <> struct bins<1> : integral_constant_2<bool, false> {};
template <> struct bins<0> : integral_constant_2<bool, false> {};
//////////////////////////////////////////////////////////////////
template <unsigned V> struct binary : binary_parser<V>, bins<V> {};
//////////////////////////////////////////////////////////////////
template <unsigned V> static constexpr auto binary_v = binary<V>::value;
//////////////////////////////////////////////////////////////////

int main() {
  // Binary to decimal usage
  cout << binary_v<101010> << endl;
  cout << binary_v<11101010> << endl;

  return 0;
}
