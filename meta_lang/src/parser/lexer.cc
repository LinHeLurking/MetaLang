#include "lexer.hpp"

#include <unordered_map>

#include "src/util/macro_util.hpp"

namespace meta_lang::parser {

std::expected<Lexer::StreamT, Lexer::Error> Lexer::Tokenize(
    const char *p) const {
  int state = int(State::kStart);
  std::deque<TokenPtr> stream;
  if (*p == EOF) {
    return stream;
  }
  // debug helper
#ifndef NDEBUG
  auto &_s = reinterpret_cast<State &>(state);
#endif
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
  FillChEq();
  FillTransitionTable();
}

std::tuple<int, const char *> Lexer::LookAhead(int state,
                                               const char *p) noexcept {
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
    case kDotMixStart: {
      if (char ch = *p; ch >= '0' && ch <= '9') {
        s = kNumMixStart;
        // this is indented fall through.
      } else {
        s = kDotEnd;
        break;
      }
    }
    case kNumMixStart: {
      for (; *p >= '0' && *p <= '9'; ++p) {
      }
      s = kIntLiteralEnd;
      if (*p == 'u') {
        p++;
        if (*p == '3' && *(p + 1) == '2') {
          p += 2;
          s = kUint32LiteralEnd;
        }
        if (*p == '6' && *(p + 1) == '4') {
          p += 2;
          s = kUint64LiteralEnd;
        }
        break;
      }
      if (*p == 'i') {
        p++;
        if (*p == '3' && *(p + 1) == '2') {
          p += 2;
          s = kInt32LiteralEnd;
        }
        if (*p == '6' && *(p + 1) == '4') {
          p += 2;
          s = kInt64LiteralEnd;
        }
      }
      if (*p == '.') {
        p++;
        for (; *p >= '0' && *p < '9'; ++p) {
        }
        s = kFloatLiteralEnd;
      }
      if (*p == 'e') {
        p++;
        for (; *p >= '0' && *p <= '9'; ++p) {
        }
        s = kDoubleLiteralEnd;
        if (*p == 'f') {
          s = kError;
        }
      }
      if (s != kError && *p == 'f') {
        ++p;
        s = kFloatLiteralEnd;
      } else if (s != kError && *p == 'd') {
        ++p;
        s = kDoubleLiteralEnd;
      }
      break;
    }
    case kIdentifierMixStart: {
      for (; isalnum(*p) || *p == '_'; ++p) {
      }
      s = kIdentifierEnd;
      break;
    }
  }
  return {int(s), p};
}

std::expected<int, Lexer::Error> Lexer::AddToken(Lexer::StreamT &stream,
                                                 Lexer::State state,
                                                 const char *token_begin,
                                                 size_t token_len) noexcept {
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
      case TokenType::kStrLiteral: {                            \
        assert(*token_begin == '"');                            \
        assert(token_begin[token_len - 1] == '"');              \
        assert(token_len >= 2);                                 \
        stream.emplace_back(t, token_begin + 1, token_len - 2); \
        break;                                                  \
      }                                                         \
      case TokenType::kIntLiteral:                              \
      case TokenType::kInt32Literal:                            \
      case TokenType::kInt64Literal:                            \
      case TokenType::kUint32Literal:                           \
      case TokenType::kUint64Literal:                           \
      case TokenType::kFloatLiteral:                            \
      case TokenType::kDoubleLiteral:                           \
      case TokenType::kIdentifier: {                            \
        stream.emplace_back(t, token_begin, token_len);         \
        break;                                                  \
      }                                                         \
    };                                                          \
    break;                                                      \
  }
  // ensure that if more states are added, compiler produces error to help you
  // change map counter.

  // 1st state is kStart, 2nd is kError, LAST_END_STATE is kEOFEnd
  static_assert(LAST_END_STATE - 2 + 1 == 40);  // 40 ending states
  switch (s) {
    default: {
      assert(false && "Error ending state!");
      E_RET(Error::kErrorChar);
    }
      MACRO_FOREACH(ADD_TOKEN, kStrLiteral, kCharLiteral, kIntLiteral,
                kInt32Literal, kInt64Literal, kUint32Literal, kUint64Literal,
                kFloatLiteral, kDoubleLiteral, kIdentifier, kAdd, kAddEq, kSub,
                kSubEq, kMul, kMulEq, kDiv, kDivEq, kMod, kModEq, kInc, kDec,
                kAssign, kEq, kNotEq, kLess, kGreater, kLessEq, kGreaterEq,
                kNot, kComment, kDot, kSemicolon, kLeftParen, kRightParen,
                kLeftCurlyBracket, kRightCurlyBracket, kLeftBracket,
                kRightBracket, kEOF);
  }
#undef ADD_TOKEN
  return 0;
}

void Lexer::FillChEq() noexcept {
  // Fill character equivalent table
  std::fill(ch_eq_, ch_eq_ + ALPHABET_SIZE, int(CharEq::kError));
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
}

void Lexer::FillTransitionTable() noexcept {
  constexpr int n_cls = int(CharEq::CHAR_EQ_MAX);

  // Fill transition table
  std::fill(transition_, transition_ + TransitionTableSize, int(State::kError));
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
      if (cls == CharEq::kEOF) continue;
      Transition(kStrLiteralEscape, cls, kStrLiteralSpin);
      if (cls == CharEq::kDoubleQuote || cls == CharEq::kBackSlash) continue;
      Transition(kStrLiteralStart, cls, kStrLiteralSpin);
      Transition(kStrLiteralSpin, cls, kStrLiteralSpin);
    }
    Transition(kStrLiteralStart, '"', kStrLiteralEnd);
    Transition(kStrLiteralStart, '\\', kStrLiteralEscape);
    Transition(kStrLiteralSpin, '\\', kStrLiteralEscape);
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
  // NumMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), CharEq::kNum, kNumMixStart);
    }
  }
  // DotMix
  {
    for (int i = 0; i < LAST_END_STATE; ++i) {
      Transition(State(i), CharEq::kDot, kDotMixStart);
    }
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
        {';', kSemicolonEnd},         {'(', kLeftParenEnd},
        {')', kRightParenEnd},        {'[', kLeftBracketEnd},
        {']', kRightBracketEnd},      {'{', kLeftCurlyBracketEnd},
        {'}', kRightCurlyBracketEnd},
    };
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      auto state = State(i);
      for (const auto [ch, target_state] : m) {
        // skip already set entries
        if (Transition(state, ch) != kError) continue;
        Transition(state, ch, target_state);
      }
    }
    // identifiers
    {
      for (int i = 0; i <= LAST_END_STATE; ++i) {
        auto s = State(i);
        Transition(s, CharEq::kCharLow, kIdentifierMixStart);
        Transition(s, CharEq::kCharUp, kIdentifierMixStart);
        Transition(s, CharEq::kUnderscore, kIdentifierMixStart);
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
}  // namespace meta_lang::parser
