// Bby C++ Library - Memory copy utility
//
// Copyright TBD
//

#pragma once

#include "gsl/gsl"

#include <type_traits>
#include <cstddef>

namespace bby {

// ByteCopy: Utility function in charge to copy trivial types into a trivial
// buffer castable to uint8_t, with a type system check and size checking check
// with GSL::SPAN
template <class T>
typename std::enable_if<std::is_trivial<T>::value>::type ByteCopy(
    gsl::span<std::byte> destination, T const source)
{
  uint32_t shift{0};

  for (std::ptrdiff_t index{0};
       index < sizeof(T)  && index <= destination.size();
       ++index, shift += 8)
  {
    destination[index] = static_cast<std::byte>((source >> shift) & 0xFF);
  }
}

template <class T, class Z>
typename std::enable_if<std::is_trivial<T>::value &&
                        std::is_trivial<Z>::value>::type
ByteCopy(Z* destination, T const source)
{
  return ByteCopy<T>({destination, sizeof(T)}, source);
}




// CreateType: Utility function in charge to construct a trivial type from a
// trivial buffer with type system check and size check with GSL::SPAN
template <class T>
typename std::enable_if<std::is_trivial<T>::value, T>::type CreateType(
    gsl::span<uint8_t const> const source)
{
  uint32_t shift{0};
  T tmp_destination{0};

  for (std::ptrdiff_t index{sizeof(T) - 1};
       index >= 0 && index <= source.size();
       --index, shift += 8)
  {
    tmp_destination |= (source[index] << shift);
  }

  return tmp_destination;
}

template <class T, class Z>
typename std::enable_if<std::is_trivial<T>::value && std::is_trivial<Z>::value,
                        T>::type
CreateType(const Z* const source)
{
  return CreateType<T>({source, source + sizeof(T)});
}

}
