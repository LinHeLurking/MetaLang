#ifndef METALANG_TOKEN_TYPE_HPP
#define METALANG_TOKEN_TYPE_HPP

#include <iostream>

namespace meta_lang::parser {
enum class TokenType {
  // literals
  kStrLiteral,
  kCharLiteral,
  kInt32Literal,
  kInt64Literal,
  kUint32Literal,
  kUint64Literal,
  kFloatLiteral,
  kDoubleLiteral,
  // keywords
  kVal,
  kFunc,
  kReturn,
  kIf,
  kFor,
  kBreak,
  kTrue,
  kFalse,
  // type names
  kStringType,
  kInt32Type,
  kInt64Type,
  kUInt32Type,
  kUint64Type,
  // operators
  kAdd,        // +
  kAddEq,      // +=
  kSub,        // -
  kSubEq,      // -=
  kMul,        // *
  kMulEq,      // *=
  kDiv,        // /
  kDivEq,      // /=
  kMod,        // %
  kModEq,      // %+
  kInc,        // ++
  kDec,        // --
  kAssign,     // =
  kEq,         // ==
  kNotEq,      // !=
  kLess,       // <
  kGreater,    // >
  kLessEq,     // <=
  kGreaterEq,  // >=
  kNot,
  // Comment is actually not added into token stream
  // It occurs here to help macro expansion.
  kComment,
  // single character token with no shared prefix
  kDot,                // .
  kSemicolon,          // ;
  kLeftParen,          // (
  kRightParen,         // )
  kLeftCurlyBracket,   // {
  kRightCurlyBracket,  // }
  kLeftBracket,        // [
  kRightBracket,       // ]
  kEOF,
  // counter
  TOKEN_TYPE_MAX,
};

inline std::ostream& operator<<(std::ostream& os, TokenType t) {
  os << int(t);
  return os;
}

}  // namespace meta_lang::parser::_lexer_detail

#endif  // METALANG_TOKEN_TYPE_HPP
