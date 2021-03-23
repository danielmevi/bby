// Bby C++ Library - Memory copy utility Test
//
// Copyright TBD
//

#include "bby/bby.h"

#include "fmt/core.h"
#include "gtest/gtest.h"

#include <array>

namespace test {

TEST(Unsigned, Byte) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  uint8_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Unsigned, TwoBytes) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  uint16_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Unsigned, FourBytes) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  uint32_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Unsigned, Eightbytes) {
  std::array<std::byte, 8> destination{static_cast<std::byte>(0)};
  uint64_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 8> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Signed, Byte) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  int8_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Signed, TwoBytes) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  int16_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Signed, FourBytes) {
  std::array<std::byte, 4> destination{static_cast<std::byte>(0)};
  int32_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 4> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Signed, Eightbytes) {
  std::array<std::byte, 8> destination{static_cast<std::byte>(0)};
  int64_t source = 1;
  bby::ByteCopy(destination, source);

  std::array<std::byte, 8> expectation{static_cast<std::byte>(0)};
  std::memcpy(expectation.data(), &source, sizeof source);
  EXPECT_EQ(destination, expectation);
}

TEST(Pointer, Byte) {}

TEST(UINTBuffer, Byte) {}

TEST(Numeric, Byte) {}

}
