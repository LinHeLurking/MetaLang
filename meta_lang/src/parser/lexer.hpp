#ifndef METALANG_LEXER_HPP
#define METALANG_LEXER_HPP

#include <cassert>
#include <deque>

#include "./char_equivalent.hpp"
#include "./lexer_state.hpp"
#include "./token.hpp"
#include "src/util/arithmetic.hpp"
#include "src/util/file_reader.hpp"

namespace meta_lang::parser {

class Lexer {
 public:
  enum class Error {
    kErrorChar,
    kEOF,
    kNotImplemented,
  };
  using CharEq = _lexer_detail::CharEq;
  using State = _lexer_detail::State;
  using StreamT = std::deque<TokenPtr>;

  static constexpr size_t ALPHABET_SIZE = 128;
  static constexpr size_t TransitionTableSize =
      size_t(State::STATUS_MAX) * size_t(CharEq::CHAR_EQ_MAX) + 1;

  std::expected<StreamT, Error> Tokenize(const char* p) const;

  Lexer();

 private:
  static constexpr int LAST_END_STATE = int(State::kEOFEnd);
  static constexpr int LAST_MIX_STATE = int(State::kNotMixStart);
  int ch_eq_[ALPHABET_SIZE];
  // pre-multiplied states
  int transition_[TransitionTableSize];

  inline void Transition(State from, char ch, State to) {
    // EOF is (-1), uint8_t(-1) is 127
    auto ch_eq = ChEq(ch);
    // ensure it's a valid char cls
    assert(ch_eq != CharEq::kError);
    Transition(from, ch_eq, to);
  }

  inline void Transition(State from, CharEq ch_eq, State to) {
    constexpr int n_state = int(State::STATUS_MAX);
    int pos = int(from) + int(ch_eq) * n_state;
    // ensure not filled before
    assert(transition_[pos] == int(State::kError));
    transition_[pos] = int(to);
  }

  inline State Transition(State from, CharEq ch_eq) {
    constexpr int n_state = int(State::STATUS_MAX);
    int pos = int(from) + int(ch_eq) * n_state;
    int t = transition_[pos];
    return State(t);
  }

  inline State Transition(State from, char ch) {
    auto ch_eq = ChEq(ch);
    return Transition(from, ch_eq);
  }

  inline void ChEq(char ch, CharEq eq) {
    constexpr int n_state = int(State::STATUS_MAX);
    ch_eq_[int(uint8_t(ch))] = int(eq) * n_state;
  }

  inline CharEq ChEq(char ch) const {
    constexpr int n_state = int(State::STATUS_MAX);
    assert(ch_eq_[int(uint8_t(ch))] % n_state == 0);
    return CharEq(ch_eq_[int(uint8_t(ch))] / n_state);
  }

  inline int ChEqPreMul(char ch) const {
    constexpr int n_state = int(State::STATUS_MAX);
    assert(ch_eq_[int(uint8_t(ch))] % n_state == 0);
    return ch_eq_[int(uint8_t(ch))];
  }

  static inline std::tuple<int, const char*> LookAhead(int state,
                                                       const char* p);
  static inline void AddToken(StreamT& stream, State state);
};
}  // namespace meta_lang::parser

#endif  // METALANG_LEXER_HPP
