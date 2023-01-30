#include <cube.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("CubeMove") {
    const auto my_face = CubeFace::UP;
    const auto my_turn = FaceTurn::ANTICLOCKWISE;

    const CubeMove my_move(my_face, my_turn);
    REQUIRE(my_move.getNotation() == "U'");
    fmt::print("{}\n", my_move.getNotation());

    const CubeMove another_move("R");
    REQUIRE(another_move.face == CubeFace::RIGHT);
    REQUIRE(another_move.turn == FaceTurn::CLOCKWISE);

    const CubeMove another_move2("B2");
    REQUIRE(another_move2.face == CubeFace::BACK);
    REQUIRE(another_move2.turn == FaceTurn::HALFTURN);

    REQUIRE_THROWS(CubeMove("A'"));
    REQUIRE_THROWS(CubeMove("U$"));

    std::vector< CubeMove > move_list = CubeMove::generateMoveList();
    fmt::print("{}\n", move_list);
}
