#ifndef METALANG_CHAR_EQUIVALENT_HPP
#define METALANG_CHAR_EQUIVALENT_HPP

namespace meta_lang::parser {
enum class CharEq {
  kNum,                // [0-9]
  kCharLow,            // [a-z]
  kCharUp,             // [A-Z]
  kWhitespace,         // ' '
  kNewline,            // '\n'
  kRewind,             // '\r'
  kZChar,              // '\0'
  kUnderscore,         // '_'
  kAdd,                // '+'
  kHyphen,             // '-'
  kStar,               // '*'
  kSlash,              // '/'
  kBackSlash,          // '\\'
  kEq,                 // '='
  kMod,                // '%'
  kSingleQuote,        // '\''
  kDoubleQuote,        // '"'
  kLeftParen,          // '('
  kRightParen,         // ')'
  kLeftCurlyBracket,   // '{'
  kRightCurlyBracket,  // '}'
  kLeftBracket,        // '['
  kRightBracket,       // ']'
  kLess,               // '<'
  kGreater,            // '>'
  kSemicolon,          // ';'
  kDot,                // '.'
  kNot,                // '!'
  kEOF,                // EOF
  kError,
  CHAR_EQ_MAX,
};
}

#endif  // METALANG_CHAR_EQUIVALENT_HPP
