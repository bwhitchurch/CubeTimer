#include <string_view>                   // for string_view, operator==, bas...

#include "catch2/catch_test_macros.hpp"  // for operator==, AssertionHandler
#include "enum.hpp"                      // for BiEnum

enum class TestEnum { RED = 42, BLUE = 2, YELLOW, GREEN, PURPLE };
constexpr BiEnum< TestEnum, std::string_view, 5 > colorNames{
	{{{TestEnum::RED, "red"},
      {TestEnum::BLUE, "blue"},
      {TestEnum::YELLOW, "yellow"},
      {TestEnum::GREEN, "green"},
      {TestEnum::PURPLE, "purple"}}}};

static_assert(colorNames[colorNames["red"]] == "red");

static_assert(colorNames[colorNames[TestEnum::YELLOW]] == TestEnum::YELLOW);

TEST_CASE("BiEnums") {
	REQUIRE(colorNames[TestEnum::BLUE] == "blue");
	REQUIRE(colorNames["purple"] == TestEnum::PURPLE);
	REQUIRE(colorNames[colorNames["green"]] == "green");
}
