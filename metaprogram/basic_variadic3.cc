#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename... Params>
vector<string> to_string(const Params&... params) {
    const auto to_string_impl = [](const auto& t) {
        stringstream ss;
        ss << t;
        return ss.str();
    };
    return {to_string_impl(params)...};
}

int main(const int, const char* const[]) {
    const auto vec = to_string("hello", 1, 5.4);

    for (const auto& it : vec) {
        cout << it << '\n';
    }

    return 1;
}
