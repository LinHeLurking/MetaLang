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
MetaParser::Char MetaParser::GetCh() {
  if (p_ >= 0) {
    return buf_[p_--];
  }
  uint8_t buf[4];
  Char ret = 0;
  *((Char*)buf) = 0;
  if (f_.peek() == EOF) {
    return EOF;
  }
  buf[0] = f_.get();

  uint8_t b4 = 0b11110;
  uint8_t b3 = 0b1110;
  uint8_t b2 = 0b110;
  uint8_t b1 = 0b0;
  uint8_t mask8 = 0b1111'1111;
  uint8_t mask6 = 0b1111'11;
  uint8_t mask4 = 0b1111;
  uint8_t mask3 = 0b111;

  if ((buf[0] >> 3) == b4) {
    buf[1] = f_.get();
    buf[2] = f_.get();
    buf[3] = f_.get();
    if (buf[1] == mask8) {
      return EOF;
    }
    assert((buf[1] >> 6) == 0b10);
    assert((buf[2] >> 6) == 0b10);
    assert((buf[3] >> 6) == 0b10);

    ret |= (buf[3] & mask6);
    ret |= uint16_t(buf[2] & mask6) << 6;
    ret |= uint32_t(buf[1] & mask6) << 12;
    ret |= uint32_t(buf[0] & mask3) << 18;
  } else if ((buf[0] >> 4) == b3) {
    buf[1] = f_.get();
    buf[2] = f_.get();
    if (buf[2] == mask8) {
      return EOF;
    }
    assert((buf[1] >> 6) == 0b10);
    assert((buf[2] >> 6) == 0b10);

    ret |= (buf[2] & mask6);
    ret |= uint16_t(buf[1] & mask6) << 6;
    ret |= uint32_t(buf[0] & mask4) << 12;
  } else if ((buf[0] >> 5) == b2) {
    buf[1] = f_.get();
    if (buf[1] == mask8) {
      return EOF;
    }
    assert((buf[1] >> 6) == 0b10);

    ret |= (buf[1] & mask6);
    ret |= uint16_t(buf[0] & mask6) << 6;
  } else if ((buf[0] >> 7) == b1) {
    ret = buf[0];
  } else {
    // unreachable
    assert(false);
  }
  return ret;
}

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
    auto cnt = CharToBytes(ch, buf, buf + 4);
    assert(cnt >= 1 && cnt <= 4);
    for (int i = 0; i < cnt; ++i) {
      ss << buf[i];
    }
  }
  auto s = ss.str();
  tokens_.emplace_back(TokenType::kIdentifier, std::move(s));
}

int8_t MetaParser::CharToBytes(MetaParser::Char ch, char* buf_begin,
                               char* buf_end) {
  std::fill(buf_begin, buf_end, 0);
  char* buf = buf_begin;
  if (ch <= 0x7F) {
    buf[0] = char(ch);
    return 1;
  }
  uint8_t b2h = 0b1100'0000;
  uint8_t b3h = 0b1110'0000;
  uint8_t b4h = 0b1111'1000;
  uint8_t th = 0b1000'0000;
  uint8_t mask6 = 0b1111'11;
  uint8_t mask5 = 0b1111'1;
  uint8_t mask4 = 0b1111;
  uint8_t mask3 = 0b111;

  if (ch <= 0x7FF) {
    buf[1] = th | (uint8_t(ch) & mask6);
    buf[0] = b2h | (uint8_t(ch >> 6) & mask5);
    return 2;
  }
  if (ch <= 0xFFFF) {
    buf[2] = th | (uint8_t(ch) & mask6);
    buf[1] = th | (uint8_t(ch >> 6) & mask6);
    buf[0] = b3h | (uint8_t(ch >> 12) & mask4);
    return 3;
  }
  if (ch <= 0x10FFFF) {
    buf[3] = th | (uint8_t(ch) & mask6);
    buf[2] = th | (uint8_t(ch >> 6) & mask6);
    buf[1] = th | (uint8_t(ch >> 12) & mask6);
    buf[0] = b4h | (uint8_t(ch >> 18) & mask3);
    return 4;
  }
  return -1;
}
}  // namespace meta_lang::meta_grammar::parser
