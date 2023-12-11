#ifndef KEYWORD_TYPE_HPP
#define KEYWORD_TYPE_HPP

#include <expected>

#include "../util/macro_util.hpp"

namespace meta_lang::parser {
enum class KeywordTypeParseError {
  kNotAKeyword,
};

#define CHECK_KEYWORD(x)       \
  if (0 == strcmp(name, #x)) { \
    return KeywordType::x;     \
  }

#define KEYWORD_TO_STR(t) \
  case KeywordType::t: {  \
    return #t;            \
  }

#define DEFINE_KEYWORD_TYPE(...)                                        \
  enum class KeywordType { __VA_ARGS__ };                               \
  std::expected<KeywordType, KeywordTypeParseError> KeywordTypeFromStr( \
      const char* name) noexcept {                                      \
    MACRO_FOREACH(CHECK_KEYWORD, __VA_ARGS__);                          \
    return std::unexpected{KeywordTypeParseError::kNotAKeyword};        \
  }                                                                     \
  const char* KeywordTypeToStr(KeywordType t) noexcept {                \
    switch (t) { MACRO_FOREACH(KEYWORD_TO_STR, __VA_ARGS__); };         \
  }                                                                     \
  std::ostream& operator<<(std::ostream& os, KeywordType t) noexcept {  \
    os << KeywordTypeToStr(t);                                          \
    return os;                                                          \
  }

DEFINE_KEYWORD_TYPE(k1, k2)

#undef DEFINE_KEYWORD_TYPE
#undef CHECK_KEYWORD
#undef KEYWORD_TO_STR
}  // namespace meta_lang::parser

#endif  // KEYWORD_TYPE_HPP
