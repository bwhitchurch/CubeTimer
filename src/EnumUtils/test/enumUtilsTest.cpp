#include "enumUtils.hpp"

#include <fmt/format.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Reflective Enum Creation") {}

TEST_CASE("Make Enum"){
    MAKE_ENUM(Color, int, YELLOW, ORANGE = 7, BLACK, GREY);
    Color my_color = Color::YELLOW;
    CHECK(my_color != Color::BLACK);
}

TEST_CASE("Reflective Enum Use") {
    enum class Color {
        RED,
        BLUE,
        GREEN = 42,
        PURPLE,
    };

    const ReflectiveEnum< Color > color_helper{
        {{Color::RED, "red"},
         {Color::BLUE, "blue"},
         {Color::GREEN, "green"},
         {Color::PURPLE, "purple"}}
    };

    CHECK(color_helper[Color::RED] == "red");
    CHECK(color_helper["blue"] == Color::BLUE);

    for (auto color : color_helper) { fmt::print("{}\n", color_helper[color]); }
}
