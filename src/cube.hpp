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
#include <fmt/core.h>  // for format_parse_context, formatter
#include <stdint.h>    // for uint8_t
#include <cstddef>     // for size_t

#include "enum.hpp"    // for BiEnum

/*!
 * @brief number of faces on a cube.
 */
constexpr size_t num_cube_faces = 6;

/*!
 * @brief CubeFace enum labels for faces of the cube.
 */
enum class CubeFace : uint8_t { UP, DOWN, RIGHT, LEFT, FRONT, BACK };

/*!
 * @brief BiEnum for mapping from CubeFace labels to quarter-turn metric
 * notation.
 */
constexpr BiEnum< CubeFace, char, num_cube_faces > cube_face_notation{
    {{{CubeFace::UP, 'U'},
      {CubeFace::DOWN, 'D'},
      {CubeFace::RIGHT, 'R'},
      {CubeFace::LEFT, 'L'},
      {CubeFace::FRONT, 'F'},
      {CubeFace::BACK, 'B'}}}};

/*!
 * @brief formatter specialization for CubeFace enum class
 */
template <> struct fmt::formatter< CubeFace > {
    /*!
     * @brief parse the format string
     *
     * @param ctx the format context.
     *
     * @return iterator to one past last parse char of the format string.
     */
    static constexpr auto parse(format_parse_context& t_ctx)
        -> decltype(t_ctx.begin()) {
        return t_ctx.end();
    }

    /*!
     * @brief formats the CubeFace element into a printable character
     *
     * @tparam FormatContext
     * @param face
     * @param ctx
     *
     * @return Format ctx output iterator;
     */
    template < typename FormatContext >
    static auto format(const CubeFace& t_face, FormatContext& t_ctx)
        -> decltype(t_ctx.out()) {
        return fmt::format_to(t_ctx.out(), "{}", cube_face_notation[t_face]);
    }
};

/*!
 * @brief Number of different turns that each face can make
 */
constexpr size_t num_turns = 3;
/*!
 * @brief FaceTurn an enum class to label the different modes for each face
 * move.
 */
enum class FaceTurn { ANTICLOCKWISE, CLOCKWISE, HALFTURN };
/*!
 * @brief BiEnum to map turn modes to their quarter-turn metric notation
 */
constexpr BiEnum< FaceTurn, char, num_turns > turn_notation{
    {{{FaceTurn::ANTICLOCKWISE, '\''},
      {FaceTurn::CLOCKWISE, '\0'},
      {FaceTurn::HALFTURN, '2'}}}};

/*!
 * @brief Array to map faces to their opposite axis partners.
 */
constexpr BiEnum< CubeFace, CubeFace, num_cube_faces > cube_face_axis_pair{
    {{{CubeFace::UP, CubeFace::DOWN},
      {CubeFace::DOWN, CubeFace::UP},
      {CubeFace::RIGHT, CubeFace::LEFT},
      {CubeFace::LEFT, CubeFace::RIGHT},
      {CubeFace::FRONT, CubeFace::BACK},
      {CubeFace::BACK, CubeFace::FRONT}}}};

#endif
