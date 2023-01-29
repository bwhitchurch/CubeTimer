#include "enumUtils.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ENUM MACROS") {
    MAKE_ENUM(Color, int, RED, GREEN, BLUE = 3, ORANGE)

    MAKE_NAMES(Color, Color, RED, GREEN, BLUE = 3, ORANGE)
    fmt::print("{}\n", Color_names);
    CHECK(Color_names[0] == "RED");

    MAKE_VALUES(Color, Color, RED, GREEN, BLUE = 3, ORANGE)
    CHECK(Color_values[0] == RED);
}

BETTER_ENUM(Color, int, RED, GREEN, ORANGE = 7, YELLOW)

TEST_CASE("BETTER_ENUM") {
    CHECK(Color::values()[0] == Color::RED);
    fmt::print("{}\n", Color::name());
    fmt::print("{}\n", Color::names());
    fmt::print("{}\n", Color::values());
    fmt::print("{}\n", Color::from_string("ORANGE"));
    fmt::print("{}\n", (+Color::RED).to_string());
}
