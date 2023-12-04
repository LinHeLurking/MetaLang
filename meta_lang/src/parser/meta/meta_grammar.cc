#include "meta_grammar.hpp"

#include <sstream>

#define RET_ON_CH_EOF(x)                       \
  if ((x) == EOF) {                            \
    return std::unexpected(ParserError::kEOF); \
  }
#define RET_ON_CH_NOT_MATCH(x, target)               \
  if ((x) != (target)) {                             \
    return std::unexpected(ParserError::kErrorChar); \
  }

namespace meta_lang::meta_grammar::parser {

std::expected<MetaParser *, ParserError> MetaParser::RightArrow() {
  auto ch1 = NextNonEmpty();
  auto ch2 = NextNonEmpty();
  RET_ON_CH_EOF(ch2);
  RET_ON_CH_NOT_MATCH(ch1, '-');
  RET_ON_CH_NOT_MATCH(ch2, '>');
  tokens_.emplace_back(TokenType::kRightArrow, "->");
  return this;
}

std::expected<MetaParser *, ParserError> MetaParser::Semicolon() {
  auto ch = NextNonEmpty();
  RET_ON_CH_EOF(ch);
  RET_ON_CH_NOT_MATCH(ch, ';');
  tokens_.emplace_back(TokenType::kSemicolon, ";");
  return this;
}

std::expected<MetaParser *, ParserError> MetaParser::Identifier() {
  std::stringstream ss;
  char buf[4];
  auto ch = NextNonEmpty();
  RET_ON_CH_EOF(ch);
  if (ch >= '0' && ch <= '9') {
    return std::unexpected(ParserError::kErrorChar);
  }
  UngetCh(ch);
  while (true) {
    ch = GetCh();
    RET_ON_CH_EOF(ch);
    if (ch == '-' || IsWhiteSpace(ch)) {
      UngetCh(ch);
      break;
    }
    auto cnt = util::CodepointToBytes(ch, buf);
    assert(cnt >= 1 && cnt <= 4);
    for (int i = 0; i < cnt; ++i) {
      ss << buf[i];
    }
  }
  auto s = ss.str();
  tokens_.emplace_back(TokenType::kIdentifier, std::move(s));
  return this;
}

std::expected<MetaParser *, ParserError> MetaParser::StrLiteral() {
  Char pre = 0;
  std::stringstream ss;
  char buf[4];

  auto ch = NextNonEmpty();
  RET_ON_CH_NOT_MATCH(ch, '\'');

  while (true) {
    ch = NextNonEmpty();
    RET_ON_CH_EOF(ch);
    if (ch == '\'' && pre != '\\') {
      UngetCh(ch);
      break;
    }
    auto cnt = util::CodepointToBytes(ch, buf);
    assert(cnt >= 1 && cnt <= 4);
    for (int i = 0; i < cnt; ++i) {
      ss << buf[i];
    }
    pre = ch;
  }

  ch = NextNonEmpty();
  RET_ON_CH_NOT_MATCH(ch, '\'');

  auto s = ss.str();
  tokens_.emplace_back(TokenType::kStrLiteral, std::move(s));
  return this;
}
std::expected<MetaParser *, ParserError> MetaParser::StrLiteralUnion() {
  do {
    auto res = StrLiteral();
    if (!res.has_value()) {
      return res;
    }
    auto ch = NextNonEmpty();
    if (ch == '|') {
      tokens_.emplace_back(TokenType::kUnion, "|");
    } else {
      UngetCh(ch);
      break;
    }
  } while (true);
  return this;
}
}  // namespace meta_lang::meta_grammar::parser
