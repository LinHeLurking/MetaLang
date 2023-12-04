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

std::expected<MetaParser *, ParserError> MetaParser::Tokenize() {
  do {
    auto res = Identifier();
    if (res.has_value()) {
      res = RightArrow();
    }
    if (res.has_value()) {
      res = StrLiteralUnion();
    }
    if (res.has_value()) {
      res = Semicolon();
    }
    if (!res.has_value()) {
      return res;
    }
    auto ch = NextNonEmpty();
    if (ch == EOF) {
      break;
    } else {
      UngetCh(ch);
    }
  } while (!reader_.IsFinished());
  return this;
}

#define VERIFY_TOKEN_TYPE(name, type)              \
  {                                                \
    if ((name).type_ != (type)) {                  \
      return std::unexpected(AstError::kBadToken); \
    }                                              \
  }
#define ENSURE_MORE_TOKEN                              \
  {                                                    \
    if (tokens_.empty()) {                             \
      return std::unexpected(AstError::kMissingToken); \
    }                                                  \
  };

std::expected<MetaParser *, AstError> MetaParser::BuildAst() {
  while (!tokens_.empty()) {
    auto id = ConsumeToken();
    ENSURE_MORE_TOKEN;
    VERIFY_TOKEN_TYPE(id, TokenType::kIdentifier);
    auto right_arrow = ConsumeToken();
    ENSURE_MORE_TOKEN;
    VERIFY_TOKEN_TYPE(right_arrow, TokenType::kRightArrow)
    auto str_literal = ConsumeToken();
    ENSURE_MORE_TOKEN;
    VERIFY_TOKEN_TYPE(str_literal, TokenType::kStrLiteral);

    auto rule = AstNode(AstNodeType::kRule);
    if (tokens_.empty()) {
      rule.children_.emplace_back(std::move(id));
      rule.children_.emplace_back(std::move(str_literal));
      break;
    } else {
      auto &t = PeekToken();
      if (t.type_ == TokenType::kSemicolon) {
        ConsumeToken();
        rule.children_.emplace_back(std::move(id));
        rule.children_.emplace_back(std::move(str_literal));
      } else if (t.type_ == TokenType::kUnion) {
        auto s_union = AstNode(AstNodeType::kStrLiteralUnion);
        s_union.children_.emplace_back(std::move(str_literal));
        // all ` | 'xxx' ` pairs.
        while (!tokens_.empty() && PeekToken().type_ == TokenType::kUnion) {
          auto t_u = ConsumeToken();
          ENSURE_MORE_TOKEN;
          str_literal = ConsumeToken();
          VERIFY_TOKEN_TYPE(str_literal, TokenType::kStrLiteral);
          s_union.children_.emplace_back(std::move(str_literal));
        }
        ENSURE_MORE_TOKEN;
        t = PeekToken();
        VERIFY_TOKEN_TYPE(t, TokenType::kSemicolon);
        ConsumeToken();
        rule.children_.emplace_back(std::move(id));
        rule.children_.emplace_back(std::move(s_union));
      } else {
        return std::unexpected(AstError::kBadToken);
      }
    }
    ast_.children_.emplace_back(std::move(rule));
  }
  return this;
}
}  // namespace meta_lang::meta_grammar::parser
