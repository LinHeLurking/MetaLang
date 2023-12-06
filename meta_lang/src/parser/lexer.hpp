#ifndef METALANG_LEXER_HPP
#define METALANG_LEXER_HPP

#include <cassert>
#include <deque>

#include "src/util/arithmetic.hpp"
#include "src/util/file_reader.hpp"

namespace meta_lang::parser {
class Token {
 public:
  enum Type {
    // literals
    kStrLiteral,
    kCharLiteral,
    kInt32Literal,
    kInt64Literal,
    kUint32Literal,
    kUint64Literal,
    kFloatLiteral,
    kDoubleLiteral,
    // keywords
    kVal,
    kFunc,
    kReturn,
    kIf,
    kFor,
    kBreak,
    kTrue,
    kFalse,
    // type names
    kStringType,
    kInt32Type,
    kInt64Type,
    kUInt32Type,
    kUint64Type,
    // operators
    kAdd,        // +
    kAddEq,      // +=
    kSub,        // -
    kSubEq,      // -=
    kMul,        // *
    kMulEq,      // *=
    kDiv,        // /
    kDivEq,      // /=
    kMod,        // %
    kModEq,      // %+
    kInc,        // ++
    kDec,        // --
    kAssign,     // =
    kEq,         // ==
    kNotEq,      // !=
    kLess,       // <
    kGreater,    // >
    kLessEq,     // <=
    kGreaterEq,  // >=
    kNot,
    // single character token with no shared prefix
    kDot,                // .
    kSemicolon,          // ;
    kLeftParen,          // (
    kRightParen,         // )
    kLeftCurlyBracket,   // {
    kRightCurlyBracket,  // }
    kLeftBracket,        // [
    kRightBracket,       // ]
    // counter
    TOKEN_TYPE_MAX,
  };

  Type t_;
  char body_[0];  // name placeholder
};
static_assert(sizeof(Token) <= 4);  // Bodies are hidden :P

class TokenPtr {
 public:
  TokenPtr() = delete;

  explicit TokenPtr(Token::Type t) {
    token_ = new Token;
    token_->t_ = t;
  }

  TokenPtr(Token::Type t, void* body, size_t body_size) {
    // handcrafted in-place construction
    auto p = new char[sizeof(Token) + body_size + 1];
    token_ = reinterpret_cast<Token*>(p);
    token_->t_ = t;
    token_->body_[body_size] = '\0';
    memcpy(p + sizeof(Token), body, body_size);
  }

  bool operator==(void* ptr) const noexcept { return token_ == ptr; }
  bool operator!=(void* ptr) const noexcept { return token_ != ptr; }

  ~TokenPtr() { free(token_); }

  [[nodiscard]] Token::Type Type() const noexcept {
    assert(token_ != nullptr);
    return token_->t_;
  }

  [[nodiscard]] const char* Name() const noexcept { return token_->body_; }

  template <class T>
    requires std::is_same_v<T, std::remove_cvref_t<T>>
  T As() const noexcept {
    return *reinterpret_cast<T*>(token_->body_);
  }

  TokenPtr* operator->() { return this; }

 private:
  Token* token_;
};

class Lexer {
 public:
  enum class Error {
    kErrorChar,
    kEOF,
    kNotImplemented,
  };
  // Some tokens share the same prefix characters.
  // Therefore, they have common start states.
  //
  // These are main state transition rails.
  //
  // LetterMix: keyword, type, identifier
  // Underscore: identifier
  // SingleQuote: char literal
  // DoubleQuote: string literal
  // Num: number literal
  //
  // OpMix: operator, comment (not a real state rail)
  // OpMix can be divided into more sub-categories
  // AddMix: +, +=, ++
  // SubMix: -, -=, --
  // MulMix: *, *=
  // SlashMix: /, /=, // (comment)
  // ModMix: %, %=,
  // LessMix: <, <=
  // GreaterMix: >, >=
  // EqMix: =, ==
  // NotMix: !, !=
  enum class State {
    // Start state
    kStart,
    kStrLiteralEnd,
    kCharLiteralEnd,
    kInt32LiteralEnd,
    kInt64LiteralEnd,
    kUint32LiteralEnd,
    kUint64LiteralEnd,
    kFloatLiteralEnd,
    kDoubleLiteralEnd,
    // keywords
    kValEnd,
    kFuncEnd,
    kReturnEnd,
    kIfEnd,
    kForEnd,
    kBreakEnd,
    kTrueEnd,
    kFalseEnd,
    // type names
    kStringTypeEnd,
    kInt32TypeEnd,
    kInt64TypeEnd,
    kUInt32TypeEnd,
    kUint64TypeEnd,
    // operators
    kAddEnd,
    kAddEqEnd,
    kSubEnd,
    kSubEqEnd,
    kMulEnd,
    kMulEqEnd,
    kDivEnd,
    kDivEqEnd,
    kModEnd,
    kModEqEnd,
    kIncEnd,  // ++
    kDecEnd,  // --
    kAssignEnd,
    kEqEnd,
    kNotEqEnd,
    kLessEnd,
    kGreaterEnd,
    kLessEqEnd,
    kGreaterEqEnd,
    kNotEnd,
    // comments
    kCommentEnd,
    // single character token with no shared prefix
    kDotEnd,                // .
    kSemicolonEnd,          // ;
    kLeftParenEnd,          // (
    kRightParenEnd,         // )
    kLeftCurlyBracketEnd,   // {
    kRightCurlyBracketEnd,  // }
    kLeftBracketEnd,        // [
    kRightBracketEnd,       // ]
    //
    // All ending states are above. You can easily check if lexer_ reaches
    // token ending by integer comparison.
    //
    kAddMixStart,
    kSubMixStart,
    kMulMixStart,
    kSlashMixStart,
    kModMixStart,
    kLessMixStart,
    kGreaterMixStart,
    kEqMixStart,
    kNotMixStart,
    //
    // All mix start states are above. You can easily check if current token is
    // prefix of another one by integer comparison
    //
    // comments
    kCommentSpin,
    // char literal
    // ill-formed character literals are checking during syntax analysis.
    kCharLiteralStart,
    kCharLiteralSpin,
    // string literal
    // ill-formed string literals are checking during syntax analysis.
    kStrLiteralStart,
    kStrLiteralSpin,
    //
    kNumStart,
    kNumSpin,
    kNumSciSpin,  // spin on exponential part
    kNumSpinI,    // 'i' in 456i32
    kNumSpinI3,   // '3' in 456i32
    kNumSpinI2,   // '2' in 456i32
    kNumSpinI6,   // '6' in 123i64
    kNumSpinI4,   // '4' in 123i64
    kNumSpinU,    // 'i' in 456u32
    kNumSpinU3,   // '3' in 456u32
    kNumSpinU2,   // '2' in 456u32
    kNumSpinU6,   // '6' in 123u64
    kNumSpinU4,   // '4' in 123u64
    // scientific number doesn't have suffix sping because they only have 1 char
    // tail 'd' or 'f'.

    // Error state.
    kError,
    // counter
    STATUS_MAX,
  };
  enum class CharEq {
    kNum,                // [0-9]
    kCharLow,            // [a-z]
    kCharUp,             // [A-Z]
    kWhitespace,         // ' ', '\n', '\r'
    kUnderscore,         // '_'
    kHyphen,             // '-'
    kStar,               // '*'
    kSlash,              // '/'
    kBackSlash,          // '\\'
    kEq,                 // '='
    kMod,                // '%'
    kSingleQuote,        // '\''
    kDoubleQuote,        // '"'
    kLeftParen,          // '('
    kRightParen,         // ')'
    kLeftCurlyBracket,   // '{'
    kRightCurlyBracket,  // '}'
    kLeftBracket,        // '['
    kRightBracket,       // ']'
    kLess,               // '<'
    kGreater,            // '>'
    kSemicolon,          // ';'
    kDot,                // '.'
    kEOF,                // EOF
    kError,
    CHAR_EQ_MAX,
  };

  static constexpr size_t ALPHABET_SIZE = 128;
  static constexpr size_t TransitionTableSize =
      size_t(State::STATUS_MAX) * size_t(CharEq::CHAR_EQ_MAX) + 1;

  std::expected<std::deque<TokenPtr>, Error> Tokenize(char* p);

  Lexer();

 private:
  static constexpr int LAST_END_STATE = int(State::kRightBracketEnd);
  static constexpr int LAST_MIX_STATE = int(State::kNotMixStart);
  int ch_eq_[ALPHABET_SIZE];
  // pre-multiplied states
  int transition_[TransitionTableSize];

  inline void Transition(State from, char ch, State to) {
    // EOF is (-1), uint8_t(-1) is 127
    auto ch_eq = CharEq(ch_eq_[int(uint8_t(ch))]);
    // ensure it's a valid char cls
    assert(ch_eq != CharEq::kError);
    Transition(from, ch_eq, to);
  }

  inline void Transition(State from, CharEq ch_eq, State to) {
    constexpr int n_state = int(CharEq::CHAR_EQ_MAX);
    int pos = int(from) + int(ch_eq) * n_state;
    // ensure not filled before
    assert(transition_[pos] == int(State::kError));
    transition_[pos] = int(to);
  }

  inline State GetTransition(State from, CharEq ch_eq) {
    constexpr int n_state = int(State::STATUS_MAX);
    int pos = int(from) + int(ch_eq) * n_state;
    int t = transition_[pos];
    return State(t);
  }

  inline State GetTransition(State from, char ch) {
    auto ch_eq = CharEq(ch_eq_[int(uint8_t(ch))]);
    return GetTransition(from, ch_eq);
  }

  inline void ChEq(char ch, CharEq eq) { ch_eq_[ch] = int(eq); }
};
}  // namespace meta_lang::parser

#endif  // METALANG_LEXER_HPP
