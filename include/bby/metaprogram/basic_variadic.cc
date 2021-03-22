#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename T>
string to_string_impl(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}
vector<string> to_string() { return {}; }

template <typename P1, typename... Params>
vector<string> to_string(const P1& param1, const Params&... params) {
    vector<string> vec;

    vec.push_back(to_string_impl(param1));

    const vector<string> otherStrings{
        to_string(params...)};  // {to_string(params2), to_string(params3),
                                // to_string(params4), ...}
    vec.insert(vec.end(), otherStrings.begin(), otherStrings.end());

    return vec;
}

int main(const int, const char* const[]) {
    const auto vec = to_string("hello", 1, 5.4);

    for (const auto& it : vec) {
        cout << it << '\n';
    }

    return 1;
}
