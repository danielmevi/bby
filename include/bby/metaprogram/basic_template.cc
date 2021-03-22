#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
string to_string(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

template <typename T>
void print(const T& t) {
    cout << t << '\n';
}

int main(const int, const char* const[]) {
    print(1);
    print("Hello world");
    print(5.3);
    cout << '\n';

    cout << to_string(1) << '\n';
    to_string("hello world");
    to_string(5.3);

    return 1;
}
