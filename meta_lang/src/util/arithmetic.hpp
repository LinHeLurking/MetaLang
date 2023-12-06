#ifndef METALANG_ARITHMETIC_HPP
#define METALANG_ARITHMETIC_HPP

#include <concepts>

namespace meta_lang::util {
template <std::integral T>
inline constexpr T Min2Pow(T k) {
  T ret = 1;
  for (; ret < k; ret <<= 1)
    ;
  return ret;
}

template <std::integral T>
inline constexpr T Ctz(T k) {
  T flag = 1;
  T ret = 0;
  for (; flag & k; ret++, flag <<= 1)
    ;
  return ret;
}
}  // namespace meta_lang::util

#endif  // METALANG_ARITHMETIC_HPP
