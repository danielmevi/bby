/* Daniel Medina Villegas
 *
 * Template metaprogramming
 *
 * Factorial puzzle
 * This is an old implementation of metraprograming code.
 * The code computes the factorial of any long number at compile time
 *
 */

#include <iostream>

//////////////////////////////////////////////////////
template <unsigned n>
struct factorial {
    enum { value = n * factorial<n - 1>::value };
};
template <>
struct factorial<0> {
    enum { value = 1 };
};
//////////////////////////////////////////////////////

int main() {
    std::cout << factorial<9>::value << std::endl;

    return 1;
}
