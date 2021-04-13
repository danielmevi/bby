#include <iostream>

struct year_t {
  unsigned value;
  constexpr year_t(unsigned N) : value(N) {}
};

struct month_t {
  unsigned value;
  constexpr month_t(unsigned N) : value(N) {}
};

struct day_t {
  unsigned value;
  constexpr day_t(unsigned N) : value(N) {}
};

constexpr year_t operator""_year(const unsigned long long int y) {
  return year_t(y);
}

constexpr month_t operator""_month(const unsigned long long int m) {
  return month_t(m);
}

constexpr day_t operator""_day(const unsigned long long int d) {
  return day_t(d);
}

template <typename T, typename Y, typename Z>
constexpr unsigned date(T p1, Y p2, Z p3) {
  return 1;
}

int main() {
  std::cout << date(2016_year, 10_month, 10_day);

  return 1;
}
