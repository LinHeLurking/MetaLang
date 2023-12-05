#ifndef METALANG_CODEPOINT_VIEW_HPP
#define METALANG_CODEPOINT_VIEW_HPP

#include <ranges>

#include "../string/utf8.hpp"

// thanks for
// https://mariusbancila.ro/blog/2020/06/06/a-custom-cpp20-range-view/

namespace meta_lang::util {
namespace detail {
namespace rng = std::ranges;
template <rng::bidirectional_range R>
  requires rng::view<R>
class CodepointView : public rng::view_interface<CodepointView<R>> {
 public:
  using BaseIterT = rng::iterator_t<R>;
  using BaseIterDiffT = std::iter_difference_t<BaseIterT>;

  class Iterator {
   public:
    using difference_type = BaseIterDiffT;
    using value_type = std::iter_value_t<BaseIterT>;
    // make sure this is a range of bytes
    static_assert(sizeof(value_type) == 1);

    bool operator==(const Iterator& rhs) const {
      return iter_ptr_ == rhs.iter_ptr_;
    }
    bool operator!=(const Iterator& rhs) const {
      return iter_ptr_ != rhs.iter_ptr_;
    }

    Iterator() = default;

    Iterator& operator++() noexcept {
      auto [codepoint, cnt] = Read();
      //      *read_ = codepoint;
      for (int i = 0; i < cnt; ++i) {
        ++*iter_ptr_;
      }
      return *this;
    }

    Iterator operator++(int) noexcept {
      auto tmp = *this;
      auto [codepoint, cnt] = Read();
      *read_ = codepoint;
      for (int i = 0; i < cnt; ++i) {
        ++*iter_ptr_;
      }
      return tmp;
    }

    uint32_t& operator*() const noexcept {
      if (*read_ == -1) {
        auto [codepoint, cnt] = Read();
        *read_ = codepoint;
      }
      *last_ = *read_;
      *read_ = -1;
      return *last_;
    }

    explicit Iterator(BaseIterT* iter)
        : iter_ptr_(iter), last_(new uint32_t), read_(new uint32_t) {
      *last_ = *read_ = -1;
    }

//    ~Iterator() {
//      delete last_;
//      delete read_;
//    }

   private:
    BaseIterT* iter_ptr_;
    uint32_t* last_;
    uint32_t* read_;

    std::pair<uint32_t, uint8_t> Read() const {
      char buf[4];
      auto tmp = *iter_ptr_;
      buf[0] = *tmp;
      ++tmp;
      buf[1] = *tmp;
      ++tmp;
      buf[2] = *tmp;
      ++tmp;
      buf[3] = *tmp;
      ++tmp;
      return BytesToCodepoint(buf);
    }
  };
  static_assert(std::input_iterator<Iterator>);
  static_assert(std::forward_iterator<Iterator>);

 public:
  CodepointView() = default;

  explicit constexpr CodepointView(R base) : base_(base) {}

  constexpr R base() const& { return base_; }
  constexpr R base() const&& { return std::move(base_); }

  constexpr auto begin() { return Iterator(&begin_); }
  constexpr auto end() { return Iterator(&end_); }

 private:
  R base_{};
  BaseIterT begin_{std::begin(base_)};
  BaseIterT end_{std::end(base_)};
};

template <class R>
CodepointView(R&& base, std::iter_difference_t<rng::iterator_t<R>>)
    -> CodepointView<rng::views::all_t<R>>;

struct CodepointViewAdaptor
    : public rng::range_adaptor_closure<CodepointViewAdaptor> {
  template <rng::viewable_range R>
  constexpr auto operator()(R&& r) const {
    return CodepointView(std::forward<R>(r));
  }

  constexpr auto operator()() const { return CodepointViewAdaptor(); }
};

template <rng::viewable_range R>
constexpr auto operator|(R&& r, CodepointViewAdaptor const& op) {
  return op(std::forward<R>(r));
}
}  // namespace detail

detail::CodepointViewAdaptor codepoint_view;
}  // namespace meta_lang::util

#endif  // METALANG_CODEPOINT_VIEW_HPP
