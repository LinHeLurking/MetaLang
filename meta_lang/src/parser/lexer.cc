#include "lexer.hpp"

#include <unordered_map>

namespace meta_lang::parser {

std::expected<std::deque<TokenPtr>, Lexer::Error>
meta_lang::parser::Lexer::Tokenize(char *p) {
  int state = int(State::kStart);
  std::deque<TokenPtr> stream;
  int token_len = 0;
  do {
    // cls is pre-multiplied
    int cls = int(ch_eq_[*p++]);
    state = int(transition_[state + cls]);
    if (state > LAST_MIX_STATE) continue;
    auto s = State(state);
    switch (s) {
      default:
        break;
      case State::kAddMixStart: {
        char ch = *p;
        if (ch != '+' && ch != '=') {
          state = int(State::kAddEnd);
        }
        break;
      }
      case State::kSubMixStart: {
        char ch = *p;
        if (ch != '-' && ch != '=') {
          state = int(State::kSubEnd);
        }
        break;
      }
      case State::kMulMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kMulEnd);
        }
        break;
      }
      case State::kSlashMixStart: {
        char ch = *p;
        if (ch != '/') {
          state = int(State::kDivEnd);
        }
        break;
      }
      case State::kModMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kModEnd);
        }
        break;
      }
      case State::kLessMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kLessEnd);
        }
        break;
      }
      case State::kGreaterMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kGreaterEnd);
        }
        break;
      }
      case State::kEqMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kAssignEnd);
        }
        break;
      }
      case State::kNotMixStart: {
        char ch = *p;
        if (ch != '=') {
          state = int(State::kNotEnd);
        }
        break;
      }
    }
  } while (state > LAST_END_STATE);

  State s = State(state);
  using enum Token::Type;
  switch (s) {
    default: {
      E_RET(Error::kNotImplemented);
    }
    case State::kAddEnd: {
      stream.emplace_back(kAdd);
      break;
    }
    case State::kAddEqEnd: {
      stream.emplace_back(kAddEq);
      break;
    }
    case State::kSubEnd: {
      stream.emplace_back(kSub);
      break;
    }
    case State::kSubEqEnd: {
      stream.emplace_back(kSubEq);
      break;
    }
    case State::kMulEnd: {
      stream.emplace_back(kMul);
      break;
    }
    case State::kMulEqEnd: {
      stream.emplace_back(kMulEq);
      break;
    }
    case State::kDivEnd: {
      stream.emplace_back(kDiv);
      break;
    }
    case State::kDivEqEnd: {
      stream.emplace_back(kDivEq);
      break;
    }
    case State::kModEnd: {
      stream.emplace_back(kMod);
      break;
    }
    case State::kModEqEnd: {
      stream.emplace_back(kModEq);
      break;
    }
    case State::kIncEnd: {
      stream.emplace_back(kInc);
      break;
    }
    case State::kDecEnd: {
      stream.emplace_back(kDec);
      break;
    }
    case State::kAssignEnd: {
      stream.emplace_back(kAssign);
      break;
    }
    case State::kEqEnd: {
      stream.emplace_back(kEq);
      break;
    }
    case State::kNotEqEnd: {
      stream.emplace_back(kNotEq);
      break;
    }
    case State::kLessEnd: {
      stream.emplace_back(kLess);
      break;
    }
    case State::kGreaterEnd: {
      stream.emplace_back(kGreater);
      break;
    }
    case State::kLessEqEnd: {
      stream.emplace_back(kLessEq);
      break;
    }
    case State::kGreaterEqEnd: {
      stream.emplace_back(kGreaterEq);
      break;
    }
    case State::kNotEnd: {
      stream.emplace_back(kNot);
    }
  }
  return stream;
}

Lexer::Lexer() {
  constexpr int n_cls = int(CharEq::CHAR_EQ_MAX);
  // Set default error entries
  std::fill(ch_eq_, ch_eq_ + ALPHABET_SIZE, int(CharEq::kError));
  std::fill(transition_, transition_ + TransitionTableSize,
            int(State::kError) * n_cls);

  // Fill character equivalent table
  for (int i = 0; i < 26; ++i) {
    ChEq('a' + i, CharEq::kCharLow);
    ChEq('A' + i, CharEq::kCharUp);
  }
  for (int i = 0; i < 10; ++i) {
    ChEq('0' + i, CharEq::kNum);
  }
  ChEq(' ', CharEq::kWhitespace);
  ChEq('\n', CharEq::kWhitespace);
  ChEq('\r', CharEq::kWhitespace);
  ChEq(EOF, CharEq::kEOF);  // pay attention to EOF!
  ChEq('_', CharEq::kUnderscore);
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
  // Fill transition table

  using enum State;
  // char literal
  {
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      Transition(State(i), '\'', kCharLiteralStart);
    }
    for (int i = 0; i < n_cls; ++i) {
      if (CharEq(i) == CharEq::kEOF) continue;
      Transition(kCharLiteralStart, CharEq(i), kCharLiteralSpin);
      Transition(kCharLiteralSpin, CharEq(i), kCharLiteralSpin);
    }
    Transition(kCharLiteralStart, '\'', kCharLiteralEnd);
    Transition(kCharLiteralSpin, '\'', kCharLiteralEnd);
  }
  // string literal
  {
    for (int i = 0; i <= LAST_END_STATE; ++i) {
      Transition(State(i), '"', kStrLiteralStart);
    }
    for (int i = 0; i < n_cls; ++i) {
      if (CharEq(i) == CharEq::kEOF) continue;
      Transition(kStrLiteralStart, CharEq(i), kStrLiteralSpin);
      Transition(kStrLiteralSpin, CharEq(i), kStrLiteralSpin);
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
      Transition(State(i), '/', kSlashMixStart);
    }
    Transition(kSlashMixStart, '/', kCommentSpin);
    Transition(kSlashMixStart, '=', kDivEqEnd);
    for (int i = 0; i < n_cls; ++i) {
      Transition(kCommentSpin, CharEq(i), kCommentSpin);
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
        if (GetTransition(state, ch) != kError) continue;
        Transition(state, ch, target_state);
      }
    }
  }
}
}  // namespace meta_lang::parser
