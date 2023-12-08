#ifndef METALANG_LEXER_STATE_HPP
#define METALANG_LEXER_STATE_HPP

namespace meta_lang::parser {
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
enum class LexerState {
  // Start state
  kStart,
  kError,  // Error state.
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
  kEOFEnd,                // file ends. "xxxEnd" names help macro expansion
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
  kCharLiteralEscape,
  kCharLiteralSpin,
  // string literal
  // ill-formed string literals are checking during syntax analysis.
  kStrLiteralStart,
  kStrLiteralEscape,
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

  // counter
  STATUS_MAX,
};
}  // namespace meta_lang::parser::_lexer_detail

#endif  // METALANG_LEXER_STATE_HPP
