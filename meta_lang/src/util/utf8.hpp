#ifndef METALANG_UTF8_HPP
#define METALANG_UTF8_HPP

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace meta_lang::util {
inline int8_t CodepointToBytes(uint32_t ch, char* buf) {
  std::fill(buf, buf + 4, 0);
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

inline std::pair<uint32_t, uint8_t> BytesToCodepoint(const char* buf) {
  uint32_t ret = 0;
  uint8_t cnt = 0;

  uint8_t b4 = 0b1111'0000;
  uint8_t b3 = 0b1110'0000;
  uint8_t b2 = 0b1100'0000;
  uint8_t th = 0b1000'0000;
  uint8_t mask8 = 0b1111'1111;
  uint8_t mask6 = 0b1111'11;
  uint8_t mask4 = 0b1111;
  uint8_t mask3 = 0b111;

  if ((buf[0] & b4) == b4) {
    if (buf[1] == mask8) {
      return {EOF, 0};
    }
    assert((buf[1] & th) == th);
    assert((buf[2] & th) == th);
    assert((buf[3] & th) == th);

    cnt = 4;
    ret |= (buf[3] & mask6);
    ret |= uint16_t(buf[2] & mask6) << 6;
    ret |= uint32_t(buf[1] & mask6) << 12;
    ret |= uint32_t(buf[0] & mask3) << 18;
  } else if ((buf[0] & b3) == b3) {
    if (buf[2] == mask8) {
      return {EOF, 0};
    }
    assert((buf[1] & th) == th);
    assert((buf[2] & th) == th);

    cnt = 3;
    ret |= (buf[2] & mask6);
    ret |= uint16_t(buf[1] & mask6) << 6;
    ret |= uint32_t(buf[0] & mask4) << 12;
  } else if ((buf[0] & b2) == b2) {
    if (buf[1] == mask8) {
      return {EOF, 0};
    }
    assert((buf[1] & th) == th);

    cnt = 2;
    ret |= (buf[1] & mask6);
    ret |= uint16_t(buf[0] & mask6) << 6;
  } else {
    cnt = 1;
    ret = uint32_t(uint8_t(buf[0]));
  }
  return {ret, cnt};
}
}  // namespace meta_lang::util

#endif  // METALANG_UTF8_HPP
