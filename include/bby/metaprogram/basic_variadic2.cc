#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename T> string to_string_impl(const T &t) {
  stringstream ss;
  ss << t;
  return ss.str();
}

template <typename... Params>
vector<string> to_string(const Params &... params) {
  return {to_string_impl(params)...}; // vector<string> {"hello", "1", "5.4"}
}

int main(const int, const char *const[]) {
  const auto vec = to_string("hello", 1, 5.4);

  for (const auto &it : vec) {
    cout << it << '\n';
  }

  return 1;
}
