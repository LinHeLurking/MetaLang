#ifndef METALANG_META_GRAMMAR_HPP
#define METALANG_META_GRAMMAR_HPP

#include <cassert>
#include <expected>
#include <fstream>
#include <string>
#include <vector>

#include "util/concept/string_like.hpp"

namespace meta_lang::meta_grammar::parser {
enum class TokenType { kSemicolon, kIdentifier, kRightArrow };

enum class ParserError {
  kErrorChar,
  kEOF,
};

class Token {
 public:
  TokenType type_;
  std::string body_;

  Token(TokenType t, StringLike auto s) : type_(t), body_(s) {}
};

class MetaParser;

using MetaParserRef = std::reference_wrapper<MetaParser>;

class MetaParser {
  using Char = uint32_t;

 public:
  explicit MetaParser(StringLike auto s)
      : f_(s, std::ios::in | std::ios::binary) {}

 private:
  Char GetCh();

  void UngetCh(Char ch) {
    assert(p_ < BUF_SIZE - 5);
    buf_[++p_] = ch;
  }

  static int8_t CharToBytes(MetaParser::Char ch, char* buf_begin,
                            char* buf_end);

  static bool IsWhiteSpace(Char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r';
  }

  Char NextNonEmpty() {
    auto ch = GetCh();
    while (IsWhiteSpace(ch)) {
      ch = GetCh();
    }
    return ch;
  }

  std::expected<MetaParserRef, ParserError> RightArrow();

  std::expected<MetaParserRef, ParserError> Semicolon();

  std::expected<MetaParserRef, ParserError> Identifier();

 private:
  constexpr static size_t BUF_SIZE = 128;
  Char buf_[BUF_SIZE]{};
  int p_ = 0;
  std::ifstream f_;
  std::vector<Token> tokens_ = {};
};
}  // namespace meta_lang::meta_grammar::parser

#endif  // METALANG_META_GRAMMAR_HPP
