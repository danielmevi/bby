#include <initializer_list>
#include <iostream>

template <typename T>
void print_impl(T& t) {
    std::cout << t << '\n';
}

template <typename... T>
void print(const T&... t) {
    (void)std::initializer_list<int>{(print_impl(t), 0)...};
}

int main(const int, const char* const[]) {
    print("Hello", 1, 3, 5.5, "World");

    return 1;
}
