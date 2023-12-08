#include "lexer.hpp"

#include <unordered_map>

#include "src/util/macro_map.hpp"

namespace meta_lang::parser {

std::expected<Lexer::StreamT, Lexer::Error> meta_lang::parser::Lexer::Tokenize(
    const char *p) const {
  int state = int(State::kStart);
  std::deque<TokenPtr> stream;
  if (*p == EOF) {
    return stream;
  }
  // debug helper
  auto &_s = reinterpret_cast<State &>(state);
  for (; state != int(State::kEOFEnd);) {
    const char *token_begin = p;
    do {
      // cls is pre-multiplied
      int cls = ChEqPreMul(*p++);
      state = int(transition_[state + cls]);
      if (state > LAST_MIX_STATE) continue;
      std::tie(state, p) = LookAhead(state, p);
    } while (state > LAST_END_STATE);
    auto token_len = size_t(p - token_begin);
    E_TRY(AddToken(stream, State(state), token_begin, token_len));
  }
  return stream;
}

Lexer::Lexer() {
  constexpr int n_cls = int(CharEq::CHAR_EQ_MAX);
  // Set default error entries
  std::fill(ch_eq_, ch_eq_ + ALPHABET_SIZE, int(CharEq::kError));
  std::fill(transition_, transition_ + TransitionTableSize, int(State::kError));

  // Fill character equivalent table
  for (int i = 0; i < 26; ++i) {
    ChEq('a' + i, CharEq::kCharLow);
    ChEq('A' + i, CharEq::kCharUp);
  }
  for (int i = 0; i < 10; ++i) {
    ChEq('0' + i, CharEq::kNum);
  }
  ChEq(' ', CharEq::kWhitespace);
  ChEq('\n', CharEq::kNewline);
  ChEq(EOF, CharEq::kEOF);  // pay attention to EOF!
  ChEq('_', CharEq::kUnderscore);
  ChEq('+', CharEq::kAdd);
  ChEq('-', CharEq::kHyphen);
  ChEq('*', CharEq::kStar);
  ChEq('/', CharEq::kSlash);
  ChEq('\\', CharEq::kBackSlash);
  ChEq('=', CharEq::kEq);
  ChEq('%', CharEq::kMod);
  ChEq('\'', CharEq::kSingleQuote);
  ChEq('"', CharEq::kDoubleQuote);
  ChEq('(', CharEq::kLeftParen);
  ChEq(')', CharEq::kRightParen);
  ChEq('{', CharEq::kLeftCurlyBracket);
  ChEq('}', CharEq::kRightCurlyBracket);
  ChEq('[', CharEq::kLeftBracket);
  ChEq(']', CharEq::kRightBracket);
  ChEq('<', CharEq::kLess);
  ChEq('>', CharEq::kGreater);
  ChEq(';', CharEq::kSemicolon);
  ChEq('.', CharEq::kDot);
  ChEq('!', CharEq::kNot);
  ChEq('\r', CharEq::kRewind);
  ChEq('\0', CharEq::kZChar);
  // Fill transition table

  using enum State;
  // char literal
  {
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      Transition(State(i), '\'', kCharLiteralStart);
    }
    for (int i = 0; i < n_cls; ++i) {
      auto cls = CharEq(i);
      if (cls == CharEq::kEOF) continue;
      Transition(kCharLiteralEscape, cls, kCharLiteralSpin);
      if (cls == CharEq::kSingleQuote || cls == CharEq::kBackSlash) continue;
      Transition(kCharLiteralStart, cls, kCharLiteralSpin);
      Transition(kCharLiteralSpin, cls, kCharLiteralSpin);
    }
    Transition(kCharLiteralStart, '\'', kCharLiteralEnd);
    Transition(kCharLiteralStart, '\\', kCharLiteralEscape);
    Transition(kCharLiteralSpin, '\\', kCharLiteralEscape);
    Transition(kCharLiteralSpin, '\'', kCharLiteralEnd);
  }
  // string literal
  {
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      Transition(State(i), '"', kStrLiteralStart);
    }
    for (int i = 0; i < n_cls; ++i) {
      auto cls = CharEq(i);
      if (cls == CharEq::kEOF || cls == CharEq::kDoubleQuote) continue;
      Transition(kStrLiteralStart, cls, kStrLiteralSpin);
      Transition(kStrLiteralSpin, cls, kStrLiteralSpin);
    }
    Transition(kStrLiteralStart, '"', kStrLiteralEnd);
    Transition(kStrLiteralSpin, '"', kStrLiteralEnd);
  }
  // AddMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '+', kAddMixStart);
    }
    Transition(kAddMixStart, '+', kIncEnd);
    Transition(kAddMixStart, '=', kAddEqEnd);
  }
  // SubMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '-', kSubMixStart);
    }
    Transition(kSubMixStart, '-', kDecEnd);
    Transition(kSubMixStart, '=', kSubEqEnd);
  }
  // MulMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '*', kMulMixStart);
    }
    Transition(kMulMixStart, '=', kMulEqEnd);
  }
  // SlashMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      auto state = State(i);
      Transition(state, '/', kSlashMixStart);
    }
    Transition(kSlashMixStart, '/', kCommentSpin);
    Transition(kSlashMixStart, '=', kDivEqEnd);
    for (int i = 0; i < n_cls; ++i) {
      auto cls = CharEq(i);
      if (cls == CharEq::kNewline) continue;
      Transition(kCommentSpin, cls, kCommentSpin);
    }
    Transition(kCommentSpin, '\n', kCommentEnd);
  }
  // ModMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '%', kModMixStart);
    }
    Transition(kModMixStart, '=', kModEqEnd);
  }
  // LessMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '<', kLessMixStart);
    }
    Transition(kLessMixStart, '=', kLessEqEnd);
  }
  // GreaterMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '>', kGreaterMixStart);
    }
    Transition(kGreaterMixStart, '=', kGreaterEqEnd);
  }
  // EqMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '=', kEqMixStart);
    }
    Transition(kEqMixStart, '=', kEqEnd);
  }
  // NotMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), '!', kNotMixStart);
    }
    Transition(kNotMixStart, '=', kNotEqEnd);
  }
  // single char token
  {
    std::unordered_map<char, State> m = {
        {';', kSemicolonEnd},        {'.', kDotEnd},
        {'(', kLeftParenEnd},        {')', kRightParenEnd},
        {'[', kLeftBracketEnd},      {']', kRightBracketEnd},
        {'{', kLeftCurlyBracketEnd}, {'}', kRightCurlyBracketEnd},
    };
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      auto state = State(i);
      for (const auto [ch, target_state] : m) {
        // skip already set entries
        if (Transition(state, ch) != kError) continue;
        Transition(state, ch, target_state);
      }
    }
    // EOF
    {
      for (int i = 0; i <= LAST_END_STATE; ++i) {
        auto state = State(i);
        Transition(state, ChEq(EOF), kEOFEnd);
      }
    }
  }
}

std::tuple<int, const char *> Lexer::LookAhead(int state, const char *p) {
  using enum State;
  auto s = State(state);
  switch (s) {
    default:
      break;
    case kAddMixStart: {
      char ch = *p;
      if (ch == '+') {
        s = kIncEnd;
        ++p;
      } else if (ch == '=') {
        s = kAddEqEnd;
        ++p;
      } else {
        s = kAddEnd;
      }
      break;
    }
    case kSubMixStart: {
      char ch = *p;
      if (ch == '-') {
        s = kDecEnd;
        ++p;
      } else if (ch == '=') {
        s = kSubEqEnd;
        ++p;
      } else {
        s = kSubEnd;
      }
      break;
    }
    case kMulMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kMulEqEnd;
        ++p;
      } else {
        s = kMulEnd;
      }
      break;
    }
    case kSlashMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kDivEqEnd;
        ++p;
      } else {
        s = kDivEnd;
      }
      break;
    }
    case kModMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kModEqEnd;
        ++p;
      } else {
        s = kModEnd;
      }
      break;
    }
    case kLessMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kLessEqEnd;
        ++p;
      } else {
        s = kLessEnd;
      }
      break;
    }
    case kGreaterMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kGreaterEqEnd;
        ++p;
      } else {
        s = kGreaterEnd;
      }
      break;
    }
    case kEqMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kEqEnd;
        ++p;
      } else {
        s = kAssignEnd;
      }
      break;
    }
    case kNotMixStart: {
      char ch = *p;
      if (ch == '=') {
        s = kNotEqEnd;
        ++p;
      } else {
        s = kNotEnd;
      }
      break;
    }
  }
  return {int(s), p};
}

std::expected<int, Lexer::Error> Lexer::AddToken(Lexer::StreamT &stream,
                                                 Lexer::State state,
                                                 const char *token_begin,
                                                 size_t token_len) {
  auto s = State(state);
  using enum TokenType;
#define ADD_TOKEN(t)                                            \
  case State::t##End: {                                         \
    switch (t) {                                                \
      default: {                                                \
        stream.emplace_back(t);                                 \
        break;                                                  \
      }                                                         \
      case TokenType::kCharLiteral: {                           \
        assert(*token_begin == '\'');                           \
        assert(token_begin[token_len - 1] == '\'');             \
        assert(token_len >= 3);                                 \
        stream.emplace_back(t, token_begin + 1, token_len - 2); \
        break;                                                  \
      }                                                         \
    };                                                          \
    break;                                                      \
  }
  // ensure that if more states are added, compiler produces error to help you
  // change map counter.

  // 1st state is kStart, 2nd is kError, LAST_END_STATE is kEOFEnd
  static_assert(LAST_END_STATE - 2 + 1 == 51);  // 51 ending states
  switch (s) {
    default: {
      assert(false && "Error ending state!");
      E_RET(Error::kErrorChar);
    }
      MACRO_MAP(51, ADD_TOKEN, kStrLiteral, kCharLiteral, kInt32Literal,
                kInt64Literal, kUint32Literal, kUint64Literal, kFloatLiteral,
                kDoubleLiteral, kVal, kFunc, kReturn, kIf, kFor, kBreak, kTrue,
                kFalse, kStringType, kInt32Type, kInt64Type, kUInt32Type,
                kUint64Type, kAdd, kAddEq, kSub, kSubEq, kMul, kMulEq, kDiv,
                kDivEq, kMod, kModEq, kInc, kDec, kAssign, kEq, kNotEq, kLess,
                kGreater, kLessEq, kGreaterEq, kNot, kComment, kDot, kSemicolon,
                kLeftParen, kRightParen, kLeftCurlyBracket, kRightCurlyBracket,
                kLeftBracket, kRightBracket, kEOF);
  }
#undef ADD_TOKEN
  return 0;
}
}  // namespace meta_lang::parser
