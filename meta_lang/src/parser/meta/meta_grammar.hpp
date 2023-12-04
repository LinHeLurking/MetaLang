#ifndef METALANG_META_GRAMMAR_HPP
#define METALANG_META_GRAMMAR_HPP

#include <cassert>
#include <expected>
#include <string>
#include <vector>

#include "src/util/concept/string_like.hpp"
#include "src/util/fs/byte_reader.hpp"
#include "src/util/string/utf8.hpp"

namespace meta_lang::meta_grammar::parser {
enum class TokenType { kSemicolon, kIdentifier, kRightArrow, kLiteralPattern };

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

class MetaParser {
  using Char = uint32_t;

 public:
  explicit MetaParser(util::StringLike auto s) : reader_(s, 128) {}

  bool IsFinished() {
    auto ch = NextNonEmpty();
    if (ch == EOF) {
      return true;
    }
    UngetCh(ch);
    return false;
  }

  Token& GetToken(int idx) { return tokens_[idx]; }

 private:
  Char GetCh() {
    if (ch_p_ >= 0) {
      return ch_buf_[ch_p_--];
    }
    if (reader_.IsFinished()) {
      return EOF;
    }
    auto buf = reader_.Get4BytesBuf();
    auto [ret, cnt] = util::BytesToCodepoint(buf);
    if (cnt == 0) {
      return EOF;
    }
    assert(cnt >= 1 && cnt <= 4);
    for (int i = cnt; i < reader_.LastRead(); ++i) {
      reader_.Unget();
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

 public:
  std::expected<MetaParser*, ParserError> RightArrow();

  std::expected<MetaParser*, ParserError> Semicolon();

  std::expected<MetaParser*, ParserError> Identifier();

  std::expected<MetaParser*, ParserError> StrLiteral();

 private:
  constexpr static int BUF_SIZE = 128;
  Char ch_buf_[BUF_SIZE]{};
  int ch_p_ = -1;
  util::ByteFileReader reader_;
  std::vector<Token> tokens_ = {};
};
}  // namespace meta_lang::meta_grammar::parser

#endif  // METALANG_META_GRAMMAR_HPP
