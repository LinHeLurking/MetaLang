#include <gtest/gtest.h>

#include "../util/try_expected.hpp"
#include "src/parser/lexer.hpp"

using namespace meta_lang::parser;

TEST(LexerCtor, Load) {
  Lexer lexer;
  const char *p = "\xFF";
  auto res = lexer.Tokenize(p);
  ASSERT_TRUE(bool(res));
}

class LexerTest : public testing::Test {
 protected:
  using enum Token::Type;
  void SetUp() override {}

  Lexer lexer_;
};

void Check(const Lexer::StreamT &stream,
           const std::vector<Token::Type> &token_types) {
  EXPECT_EQ(stream.size(), token_types.size());
  auto i = stream.begin();
  auto j = token_types.begin();
  for (; i != stream.end(); ++i, ++j) {
    EXPECT_EQ(i->Type(), *j);
  }
}

TEST_F(LexerTest, SingleChar) {
  const char *p = ";.)(][}{\xFF";
  using enum Token::Type;
  std::vector<Token::Type> token_types = {
      kSemicolon,    kDot,         kRightParen,        kLeftParen,
      kRightBracket, kLeftBracket, kRightCurlyBracket, kLeftCurlyBracket,
      kEOF};
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, token_types);
}

TEST_F(LexerTest, PrefixOp) {
  using enum Token::Type;
  {
    const char *p = "===!==+++++=\xFF";
    std::vector<Token::Type> token_types = {kEq,  kAssign, kNotEq, kAssign,
                                            kInc, kInc,    kAddEq, kEOF};
    auto stream = T_TRY(lexer_.Tokenize(p));
    Check(stream, token_types);
  }
  {
    const char *p = "---=--=!=---\xFF";
    std::vector<Token::Type> token_types = {kDec,   kSubEq, kDec, kAssign,
                                            kNotEq, kDec,   kSub, kEOF};
    auto stream = T_TRY(lexer_.Tokenize(p));
    Check(stream, token_types);
  }
  {
    const char *p = "***===!=+--+-++==-\xFF";
    std::vector<Token::Type> token_types = {kMul, kMul, kMulEq, kEq,  kNotEq,
                                            kAdd, kDec, kAdd,   kSub, kInc,
                                            kEq,  kSub, kEOF};
    auto stream = T_TRY(lexer_.Tokenize(p));
    Check(stream, token_types);
  }
}
