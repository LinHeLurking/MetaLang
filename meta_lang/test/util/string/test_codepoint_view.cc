#include <gtest/gtest.h>

#include "src/util/fs/file_range.hpp"
#include "src/util/string/codepoint_view.hpp"

using namespace meta_lang::util;

static_assert(std::input_iterator<detail::CodepointView<FileRange>::Iterator>);
static_assert(std::ranges::range<detail::CodepointView<FileRange>>);
static_assert(std::ranges::input_range<detail::CodepointView<FileRange>>);
static_assert(std::ranges::forward_range<detail::CodepointView<FileRange>>);
static_assert(std::ranges::view<detail::CodepointView<FileRange>>);

static_assert(
    std::input_iterator<detail::CodepointView<std::string_view>::Iterator>);
static_assert(std::ranges::range<detail::CodepointView<std::string_view>>);
static_assert(
    std::ranges::input_range<detail::CodepointView<std::string_view>>);
static_assert(
    std::ranges::forward_range<detail::CodepointView<std::string_view>>);
static_assert(std::ranges::view<detail::CodepointView<std::string_view>>);

TEST(CodePointView, String) {
  {
    std::string s = "123-456";
    std::string_view sv{s};
    auto v = sv | codepoint_view;
    auto it = v.begin();
    static_assert(std::is_same_v<decltype(*it), uint32_t&>);
    EXPECT_EQ(*it, '1');
    ++it;
    EXPECT_EQ(*it, '2');
    ++it;
    ++it;
    EXPECT_EQ(*it, '-');
  }
  {
    std::string s = "abc==xyz";
    auto v = std::string_view(s) | codepoint_view();
    auto it = v.begin();
    EXPECT_EQ(*(it++), 'a');
    EXPECT_EQ(*(it++), 'b');
    EXPECT_EQ(*(it++), 'c');
    EXPECT_EQ(*(it++), '=');
    EXPECT_EQ(*(it++), '=');
    EXPECT_EQ(*(it++), 'x');
    EXPECT_EQ(*(it++), 'y');
    EXPECT_EQ(*(it++), 'z');
  }
  //  {
  //    std::string s = "abc==xyz";
  //    auto res = std::string_view(s) | codepoint_view() |
  //               std::ranges::to<std::vector<uint32_t>>();
  //    std::vector<uint32_t> target = {97, 98, 99, 45, 120, 121, 122};
  //    EXPECT_EQ(res.size(), target.size());
  //    for (int i = 0; i < res.size(); ++i) {
  //      EXPECT_EQ(res[i], target[i]);
  //    }
  //  }
}
