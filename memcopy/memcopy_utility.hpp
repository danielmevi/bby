// Utility
//

#pragma once


/// @name ByteCopy
/// @brief Portable and well enough for production JLR function to copy built-in
/// types into a byte buffer
/// @param[out] destination
/// @param[in] source
template <class T>
typename std::enable_if<std::is_trivial<T>::value>::type ByteCopy(
    gsl::span<uint8_t> destination, T const source)
{
  uint32_t shift{0};

  for (std::ptrdiff_t index{sizeof(T) - 1};
       index >= 0 && index <= destination.size();
       --index, shift += 8)
  {
    destination[index] = (source >> shift) & 0xFF;
  }
}

template <class T, class Z>
typename std::enable_if<std::is_trivial<T>::value &&
                        std::is_trivial<Z>::value>::type
ByteCopy(Z* destination, T const source)
{
  return ByteCopy<T>({destination, sizeof(T)}, source);
}





/// @name CreateType
/// @brief Portable and well enough for production JLR function to copy buffer
/// bytes into built-in type
/// @param[in] source
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
