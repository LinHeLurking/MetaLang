#ifndef METALANG_META_GRAMMAR_HPP
#define METALANG_META_GRAMMAR_HPP

#include <cassert>
#include <expected>
#include <fstream>
#include <string>
#include <vector>

#include "src/util/concept/string_like.hpp"
#include "src/util/string/utf8.hpp"

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

  Token(TokenType t, util::StringLike auto s) : type_(t), body_(s) {}
};

class MetaParser;

using MetaParserRef = std::reference_wrapper<MetaParser>;

class MetaParser {
  using Char = uint32_t;

 public:
  explicit MetaParser(util::StringLike auto s)
      : f_(s, std::ios::in | std::ios::binary) {}

 private:
  Char GetCh() {
    if (ch_p_ >= 0) {
      return ch_buf_[ch_p_--];
    }
    if (f_.eof()) {
      return EOF;
    }
    char buf[4];
    f_.read(buf, 4);
    auto [ret, cnt] = util::BytesToCodepoint(buf);
    for (int i = 4; i > cnt; --i) {
      f_.unget();
    }
    return ret;
  }

  void UngetCh(Char ch) {
    assert(ch_p_ < BUF_SIZE - 5);
    ch_buf_[++ch_p_] = ch;
  }

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
  Char ch_buf_[BUF_SIZE]{};
  int ch_p_ = 0;
  std::ifstream f_;
  std::vector<Token> tokens_ = {};
};
}  // namespace meta_lang::meta_grammar::parser

#endif  // METALANG_META_GRAMMAR_HPP
