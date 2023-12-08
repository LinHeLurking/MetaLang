#include <gtest/gtest.h>

#include <ranges>

#include "../util/try_expected.hpp"
#include "src/parser/lexer.hpp"

using namespace meta_lang::parser;

TEST(LexerCtor, Load) {
  Lexer lexer;
  const char *p = "\xFF";
  auto res = lexer.Tokenize(p);
  ASSERT_TRUE(bool(res));
}

auto to_ptr = std::views::transform([](TokenType t) { return TokenPtr(t); });
auto to_vec = std::ranges::to<std::vector<TokenPtr>>();

class LexerTest : public testing::Test {
 protected:
  using enum TokenType;
  void SetUp() override {}

  Lexer lexer_;
};

void Check(const Lexer::StreamT &stream, const std::vector<TokenPtr> &tokens) {
  EXPECT_EQ(stream.size(), tokens.size());
  using enum TokenType;
  auto i = stream.begin();
  auto j = tokens.begin();
  for (; i != stream.end(); ++i, ++j) {
    const auto &a = *i, &b = *j;
    EXPECT_EQ(a->Type(), b->Type());
    switch (a->Type()) {
      default: {
        break;
      }
      case kCharLiteral: {
        auto a_literal = a->AsStr(), b_literal = b->AsStr();
        EXPECT_TRUE(strcmp(a_literal, b_literal) == 0);
        break;
      }
    }
  }
}

TEST_F(LexerTest, SingleChar) {
  const char *p = ";.)(][}{\xFF";
  std::vector<TokenType> token_types = {
      kSemicolon,    kDot,         kRightParen,        kLeftParen,
      kRightBracket, kLeftBracket, kRightCurlyBracket, kLeftCurlyBracket,
      kEOF};
  auto tokens = token_types | to_ptr | to_vec;
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, PrefixOp_0) {
  const char *p = "===!==+++++=\xFF";
  std::vector<TokenType> token_types = {kEq,  kAssign, kNotEq, kAssign,
                                        kInc, kInc,    kAddEq, kEOF};
  auto tokens = token_types | to_ptr | to_vec;
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, PrefixOp_1) {
  const char *p = "---=--=!=---\xFF";
  std::vector<TokenType> token_types = {kDec,   kSubEq, kDec, kAssign,
                                        kNotEq, kDec,   kSub, kEOF};
  auto tokens = token_types | to_ptr | to_vec;
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, PrefixOp_2) {
  const char *p = "***===!=+--+-++==-\xFF";
  std::vector<TokenType> token_types = {kMul, kMul, kMulEq, kEq,  kNotEq,
                                        kAdd, kDec, kAdd,   kSub, kInc,
                                        kEq,  kSub, kEOF};
  auto tokens = token_types | to_ptr | to_vec;
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, CharLiteral) {
  const char *p = "'a''b''c''d'--'e'\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kCharLiteral, "a"),
      TokenPtr(kCharLiteral, "b"),
      TokenPtr(kCharLiteral, "c"),
      TokenPtr(kCharLiteral, "d"),
      TokenPtr(kDec),
      TokenPtr(kCharLiteral, "e"),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, CharLiteralEscape_0) {
  const char *p = "'\\n'*'\\r'+'\\0'\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kCharLiteral, "\\n"), TokenPtr(kMul),
      TokenPtr(kCharLiteral, "\\r"), TokenPtr(kAdd),
      TokenPtr(kCharLiteral, "\\0"), TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, CharLiteralEscape_1) {
  const char *p = "++--'\\0'--++'\\n'**'\\\\'\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kInc), TokenPtr(kDec), TokenPtr(kCharLiteral, "\\0"),
      TokenPtr(kDec), TokenPtr(kInc), TokenPtr(kCharLiteral, "\\n"),
      TokenPtr(kMul), TokenPtr(kMul), TokenPtr(kCharLiteral, "\\\\"),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}
