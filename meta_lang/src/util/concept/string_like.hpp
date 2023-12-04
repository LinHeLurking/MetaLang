#ifndef METALANG_STRING_LIKE_HPP
#define METALANG_STRING_LIKE_HPP

#include <string_view>
#include <type_traits>

namespace meta_lang::util {
// https://stackoverflow.com/questions/67331445/concept-for-string-like-object
template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view>;
}  // namespace meta_lang::util

#endif  // METALANG_STRING_LIKE_HPP
