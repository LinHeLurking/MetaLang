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

std::expected<std::reference_wrapper<MetaParser>, ParserError>
MetaParser::RightArrow() {
  auto ch1 = NextNonEmpty();
  auto ch2 = NextNonEmpty();
  RET_ON_CH_EOF(ch2);
  RET_ON_CH_NOT_MATCH(ch1, '-');
  RET_ON_CH_NOT_MATCH(ch2, '>');
  tokens_.emplace_back(TokenType::kRightArrow, "->");
}

std::expected<std::reference_wrapper<MetaParser>, ParserError>
MetaParser::Semicolon() {
  auto ch = NextNonEmpty();
  RET_ON_CH_EOF(ch);
  RET_ON_CH_NOT_MATCH(ch, ';');
  tokens_.emplace_back(TokenType::kSemicolon, ";");
}
std::expected<std::reference_wrapper<MetaParser>, ParserError>
MetaParser::Identifier() {
  std::stringstream ss;
  char buf[4];
  auto ch = NextNonEmpty();
  RET_ON_CH_EOF(ch);
  UngetCh(ch);
  while (true) {
    ch = GetCh();
    RET_ON_CH_EOF(ch);
    if (IsWhiteSpace(ch)) {
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
}
}  // namespace meta_lang::meta_grammar::parser
