#ifndef KEYWORD_TYPE_HPP
#define KEYWORD_TYPE_HPP

#include <expected>
#include <iostream>

#include "../util/macro_util.hpp"
#include "./lexer_error.hpp"

namespace meta_lang::parser {

#define CHECK_KEYWORD(x)                    \
  if (0 == strcmp(name, XSTR(SECOND(x)))) { \
    return KeywordType::FIRST(x);           \
  }

#define KEYWORD_TO_STR(t)       \
  case KeywordType::FIRST(t): { \
    return XSTR(SECOND(t));     \
  }

#define DEFINE_KEYWORD_TYPE(...)                                              \
  enum class KeywordType { MACRO_FOREACH_COMMA(FIRST, __VA_ARGS__) };         \
  inline std::expected<KeywordType, LexerError> KeywordTypeFromStr(           \
      const char* name) noexcept {                                            \
    MACRO_FOREACH(CHECK_KEYWORD, __VA_ARGS__);                                \
    return std::unexpected{LexerError::kNotAKeyword};                         \
  }                                                                           \
  inline const char* KeywordTypeToStr(KeywordType t) noexcept {               \
    switch (t) { MACRO_FOREACH(KEYWORD_TO_STR, __VA_ARGS__); };               \
  }                                                                           \
  inline std::ostream& operator<<(std::ostream& os, KeywordType t) noexcept { \
    os << KeywordTypeToStr(t);                                                \
    return os;                                                                \
  }

DEFINE_KEYWORD_TYPE((kInt32, Int32), (kInt64, Int64), (kUint32, Uint32),
                    (kUint64, Uint64), (kChar, Char), (kString, String));

#undef DEFINE_KEYWORD_TYPE
#undef CHECK_KEYWORD
#undef KEYWORD_TO_STR
}  // namespace meta_lang::parser

#endif  // KEYWORD_TYPE_HPP
