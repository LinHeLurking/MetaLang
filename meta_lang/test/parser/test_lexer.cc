#include <gtest/gtest.h>

#include <ranges>

#include "../util/try_expected.hpp"
#include "src/parser/keyword_type.hpp"
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
  ASSERT_EQ(stream.size(), tokens.size());
  using enum TokenType;
  auto i = stream.begin();
  auto j = tokens.begin();
  for (; i != stream.end(); ++i, ++j) {
    EXPECT_EQ(i->Type(), j->Type());
    switch (i->Type()) {
      default: {
        break;
      }
      case kInt32Literal:
      case kUint32Literal:
      case kInt64Literal:
      case kUint64Literal:
      case kFloatLiteral:
      case kDoubleLiteral:
      case kStrLiteral:
      case kCharLiteral:
      case kIdentifier: {
        auto a_literal = i->AsStr(), b_literal = j->AsStr();
        EXPECT_TRUE(strcmp(a_literal, b_literal) == 0);
        break;
      }
      case kKeyword: {
        auto a_keyword = i->As<KeywordType>(), b_keyword = j->As<KeywordType>();
        EXPECT_EQ(a_keyword, b_keyword);
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

TEST_F(LexerTest, StrLiteral) {
#define LITERAL \
  "slakdjflkas asl;kjfkl sfkljaslk kslaf' aslkdfj las alskjdf l120-398-012"
  const char *p = "\"" LITERAL "\"\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kStrLiteral, LITERAL),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
#undef LITERAL
}

TEST_F(LexerTest, StrLiteralEscape_0) {
#define LITERAL "slakdjflkas asl;kjf\\\"kl sf\\\nkljas\\\"lk kslaf'''-398-012"
  const char *p = "\"" LITERAL "\"\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kStrLiteral, LITERAL),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
#undef LITERAL
}

TEST_F(LexerTest, NumLiteralInt_0) {
  const char *p = "123321;90219;\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kIntLiteral, "123321"),
      TokenPtr(kSemicolon),
      TokenPtr(kIntLiteral, "90219"),
      TokenPtr(kSemicolon),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, NumLiteralInt_1) {
  const char *p = "123u32;321u64;123i32;0912380989342i64\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kUint32Literal, "123u32"),          TokenPtr(kSemicolon),
      TokenPtr(kUint64Literal, "321u64"),          TokenPtr(kSemicolon),
      TokenPtr(kInt32Literal, "123i32"),           TokenPtr(kSemicolon),
      TokenPtr(kInt64Literal, "0912380989342i64"), TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, NumLiteralFP_0) {
  const char *p = "1.;0.;23.f;32.d;.42f;.51d\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kFloatLiteral, "1."),    TokenPtr(kSemicolon),
      TokenPtr(kFloatLiteral, "0."),    TokenPtr(kSemicolon),
      TokenPtr(kFloatLiteral, "23.f"),  TokenPtr(kSemicolon),
      TokenPtr(kDoubleLiteral, "32.d"), TokenPtr(kSemicolon),
      TokenPtr(kFloatLiteral, ".42f"),  TokenPtr(kSemicolon),
      TokenPtr(kDoubleLiteral, ".51d"), TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, NumLiteralFP_1) {
  const char *p = "12.34;56.78d;00.001f\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kFloatLiteral, "12.34"),   TokenPtr(kSemicolon),
      TokenPtr(kDoubleLiteral, "56.78d"), TokenPtr(kSemicolon),
      TokenPtr(kFloatLiteral, "00.001f"), TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, NumLiteralFP_2) {
  const char *p = "1e9;111.e9;.11e8\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kDoubleLiteral, "1e9"),    TokenPtr(kSemicolon),
      TokenPtr(kDoubleLiteral, "111.e9"), TokenPtr(kSemicolon),
      TokenPtr(kDoubleLiteral, ".11e8"),  TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, Identifier_0) {
  const char *p = "aa=_bb;x==yyy;a++;\xFF";
  std::vector<TokenPtr> tokens = {
      TokenPtr(kIdentifier, "aa"),  TokenPtr(kAssign),
      TokenPtr(kIdentifier, "_bb"), TokenPtr(kSemicolon),
      TokenPtr(kIdentifier, "x"),   TokenPtr(kEq),
      TokenPtr(kIdentifier, "yyy"), TokenPtr(kSemicolon),
      TokenPtr(kIdentifier, "a"),   TokenPtr(kInc),
      TokenPtr(kSemicolon),         TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, tokens);
}

TEST_F(LexerTest, Keyword_0) {
  const char *p = "Int32 a = b;String x = y;\xFF";
  std::vector<TokenPtr> toknes = {
      TokenPtr(kKeyword, KeywordType::kInt32),
      TokenPtr(kIdentifier, "a"),
      TokenPtr(kAssign),
      TokenPtr(kIdentifier, "b"),
      TokenPtr(kSemicolon),
      TokenPtr(kKeyword, KeywordType::kString),
      TokenPtr(kIdentifier, "x"),
      TokenPtr(kAssign),
      TokenPtr(kIdentifier, "y"),
      TokenPtr(kSemicolon),
      TokenPtr(kEOF),
  };
  auto stream = T_TRY(lexer_.Tokenize(p));
  Check(stream, toknes);
}
