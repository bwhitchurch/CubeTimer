#include <string_view>                  // for string_view, operator==, bas...

#include "catch2/catch_test_macros.hpp" // for operator==, AssertionHandler
#include "enum.hpp"                     // for BiEnum

enum class TestEnum { RED = 42, BLUE = 2, YELLOW, GREEN, PURPLE };
constexpr BiEnum< TestEnum, std::string_view, 5 > color_names{
    {{{TestEnum::RED, "red"},
      {TestEnum::BLUE, "blue"},
      {TestEnum::YELLOW, "yellow"},
      {TestEnum::GREEN, "green"},
      {TestEnum::PURPLE, "purple"}}}};

static_assert(color_names[color_names["red"]] == "red");

static_assert(color_names[color_names[TestEnum::YELLOW]] == TestEnum::YELLOW);

TEST_CASE("BiEnums") {
    REQUIRE(color_names[TestEnum::BLUE] == "blue");
    REQUIRE(color_names["purple"] == TestEnum::PURPLE);
    REQUIRE(color_names[color_names["green"]] == "green");
}
