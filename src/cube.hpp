/*!
 * @file cube.hpp
 * @brief Contains definitions of constants and enums related to representing a
 * cube.
 * @author Brandon M. Whitchurch
 * @version 0.0.1
 * @date 2023-01-16
 */
#ifndef CUBE_HPP
#define CUBE_HPP
#include "enumUtils.hpp"

#include <cstddef> // for size_t
#include <exception>
#include <stdexcept>
#include <stdint.h> // for uint8_t
#include <unordered_map>
#include <unordered_set>

#include <fmt/compile.h> // for format_parse_context, formatter
#include <fmt/core.h>    // for format_parse_context, formatter

/*!
 * @brief number of faces on a cube.
 */
constexpr size_t num_cube_faces = 6;

BETTER_ENUM(CubeFace, uint8_t, UP, DOWN, RIGHT, LEFT, FRONT, BACK)

/*!
 * @brief Number of different turns that each face can make
 */
constexpr size_t num_turns = 3;

BETTER_ENUM(FaceTurn, uint8_t, ANTICLOCKWISE, CLOCKWISE, HALFTURN)

constexpr auto makeFirstQuery(const auto& t_first_val) {
    return [t_first_val](auto t_pair_val) {
        return t_pair_val.first == t_first_val;
    };
}

constexpr auto makeSecondQuery(const auto& t_second_val) {
    return [t_second_val](auto t_pair_val) {
        return t_pair_val.second == t_second_val;
    };
}

struct CubeMove {
    constexpr static std::array< std::pair< CubeFace, char >, CubeFace::size() >
        face_notation{
            {{CubeFace::UP, 'U'},
             {CubeFace::DOWN, 'D'},
             {CubeFace::RIGHT, 'R'},
             {CubeFace::LEFT, 'L'},
             {CubeFace::FRONT, 'F'},
             {CubeFace::BACK, 'B'}}
    };

    constexpr static std::array< std::pair< FaceTurn, char >, FaceTurn::size() >
        turn_notation{
            {{FaceTurn::ANTICLOCKWISE, '\''},
             {FaceTurn::CLOCKWISE, '\0'},
             {FaceTurn::HALFTURN, '2'}}
    };

    constexpr static CubeFace getFace(const char& t_c) {
        const auto* face_ptr = std::find_if(
            face_notation.begin(), face_notation.end(), makeSecondQuery(t_c)
        );
        if (face_ptr == face_notation.end()) {
            throw std::invalid_argument(fmt::format(
                "{} is not recognized notation for a cube face\n", t_c
            ));
        }
        return face_ptr->first;
    }

    constexpr static FaceTurn getTurn(const char& t_c) {
        const auto* turn_ptr = std::find_if(
            turn_notation.begin(), turn_notation.end(), makeSecondQuery(t_c)
        );
        if (turn_ptr == turn_notation.end()) {
            throw std::invalid_argument(fmt::format(
                "{} is not recognized notation for a face turn\n", t_c
            ));
        }
        return turn_ptr->first;
    }

    CubeFace face;
    FaceTurn turn;

    explicit constexpr CubeMove(const CubeFace& t_face, const FaceTurn& t_turn)
        : face(t_face), turn(t_turn) {}

    explicit constexpr CubeMove(const std::string_view t_notation)
        : face(getFace(t_notation[0])), turn(getTurn(t_notation[1])) {}

    [[nodiscard]] constexpr std::string getNotation() const {
        const auto* face_ptr = std::find_if(
            face_notation.begin(), face_notation.end(), makeFirstQuery(face)
        );
        const auto* turn_ptr = std::find_if(
            turn_notation.begin(), turn_notation.end(), makeFirstQuery(turn)
        );

        return std::string(&(face_ptr->second), 1)
             + std::string(&(turn_ptr->second), 1);
    }

    static std::vector< CubeMove > generateMoveList() {
        std::vector< CubeMove > move_list;
        move_list.reserve(CubeFace::size() * FaceTurn::size());
        for (auto face : CubeFace::values()) {
            for (auto turn : FaceTurn::values()) {
                move_list.emplace_back(face, turn);
            }
        }
        return move_list;
    }
};

template <> struct fmt::formatter< CubeMove > {
    template < typename ParseCtx > constexpr auto parse(ParseCtx& t_ctx) const {
        return t_ctx.begin();
    }

    template < typename FormatCtx >
    constexpr auto format(const CubeMove& t_move, FormatCtx& t_ctx) const {
        return format_to(t_ctx.out(), "{}", t_move.getNotation());
    }
};

#endif
