#include "ppUtils.hpp"

#include <string>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic Function Macros", "[macro][preprocessor][pp]") {
    SECTION("ID") {
        SECTION("char input") { REQUIRE(MM_ID('a') == 'a'); }
        SECTION("string input") {
            REQUIRE(MM_ID(std::string("ppUtils")) == std::string("ppUtils"));
        }
        SECTION("integer input") { REQUIRE(MM_ID(1) == 1); }
        SECTION("floating input") { REQUIRE(MM_ID(1.0) == 1.0); }
    }

    SECTION("CONCAT") {
        const int a12 = 8;
        REQUIRE(MM_CONCAT(a, 12) == 8);
    }
    SECTION("EXPAND") {
        CHECK(
            std::string(MM_STRINGIFY_M(MM_ID(MM_ID T_PARENS 2.0)))
            == std::string("MM_ID () 2.0")
        );

        CHECK(MM_EXPAND(MM_ID T_PARENS 2.0) == 2.0);
    }

    SECTION("FOR_EACH") {
        const std::string res = MM_STRINGIFY_M(MM_FOR_EACH(MM_ID, 1, 2, 3, 4, 5));
        REQUIRE(res == "1 2 3 4 5");
    }

    SECTION("FOLD") {
        REQUIRE(
                std::string(MM_STRINGIFY_M(MM_FOLD_LEFT(MM_CONCAT, a, b, c, d)))
                    == "abcd"
                    );
    }
    SECTION("NARG") {
        CHECK(MM_COUNT_ARGS(a, b, c, d) == 4);
    }
}
