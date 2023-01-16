#include "catch2/catch_test_macros.hpp"
void sayHello();

TEST_CASE("SayHello","[libfoo]") {
	sayHello();
    REQUIRE(true);
}
