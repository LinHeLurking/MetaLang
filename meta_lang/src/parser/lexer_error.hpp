#ifndef LEXER_ERROR_HPP
#define LEXER_ERROR_HPP

namespace meta_lang::parser {
enum class LexerError {
  kErrorChar,
  kEOF,
  kNotAKeyword,
  kNotImplemented,
};
}

#endif  // LEXER_ERROR_HPP
