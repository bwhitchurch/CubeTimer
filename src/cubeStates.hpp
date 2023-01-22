#ifndef CUBE_STATES_HPP
#define CUBE_STATES_HPP
#include <fmt/core.h>  // for format_parse_context, formatter
#include <algorithm>   // for equal
#include <array>       // for array, operator==
#include <cstddef>     // for size_t
#include <string_view> // for string_view

#include "cube.hpp"    // for CubeFace, numCubeFaces
#include "enum.hpp"    // for BiEnum

struct CubeSymmetry {
    std::array< CubeFace, num_cube_faces > m_state;

    CubeSymmetry operator&(const CubeSymmetry& t_other) const {
        CubeSymmetry result{};
        for (size_t i = 0; i < num_cube_faces; ++i) {
            result[i] = (*this)[t_other[i]];
        }
        return result;
    }

    CubeSymmetry operator-() const {
        CubeSymmetry result{};
        for (size_t i = 0; i < num_cube_faces; ++i) {
            result[m_state.at(i)] = CubeFace(i);
        }
        return result;
    }

    bool operator==(const CubeSymmetry& t_other) const {
        return m_state == t_other.m_state;
    }

    constexpr CubeFace operator[](const CubeFace& t_face) const {
        return m_state.at(static_cast< size_t >(t_face));
    }

    constexpr CubeFace operator[](const size_t& t_i) const {
        return m_state.at(t_i);
    }

    CubeFace& operator[](const CubeFace& t_face) {
        return m_state.at(static_cast< size_t >(t_face));
    }

    CubeFace& operator[](const size_t& t_i) { return m_state.at(t_i); }
};

constexpr BiEnum< CubeFace, std::string_view, num_cube_faces > color_scheme{
    {{{CubeFace::UP, "White"},
      {CubeFace::DOWN, "Yellow"},
      {CubeFace::RIGHT, "Red"},
      {CubeFace::LEFT, "Orange"},
      {CubeFace::FRONT, "Green"},
      {CubeFace::BACK, "Blue"}}}

};

template <> struct fmt::formatter< CubeSymmetry > {
    static constexpr auto parse(format_parse_context& t_ctx)
        -> decltype(t_ctx.begin()) {
        return t_ctx.end();
    }

    template < typename FormatContext >
    static auto
    format(const CubeSymmetry& t_cube_symm, FormatContext& t_ctx) 
        -> decltype(t_ctx.out()) {
        constexpr std::string_view fill_blank = "        ";
        constexpr std::string_view fill_upper = "‾‾‾‾‾‾‾‾";
        constexpr std::string_view fill_lower = "________";
        fmt::format_to(
            t_ctx.out(),
            "\n {0}|{1}|\n {0}|{0}|\n {0}|{2:^8s}|\n {0}|{0}|\n",
            fill_blank,
            fill_upper,
            color_scheme[t_cube_symm[CubeFace::BACK]]
        );

        fmt::format_to(
            t_ctx.out(),
            "|{0}|{0}|{0}|{0}|\n|{1}|{1}|{1}|{1}|\n",
            fill_upper,
            fill_blank
        );
        fmt::format_to(
            t_ctx.out(),
            "|{0:^8s}|{1:^8s}|{2:^8s}|{3:^8s}|\n",
            color_scheme[t_cube_symm[CubeFace::LEFT]],
            color_scheme[t_cube_symm[CubeFace::UP]],
            color_scheme[t_cube_symm[CubeFace::RIGHT]],
            color_scheme[t_cube_symm[CubeFace::DOWN]]
        );
        fmt::format_to(
            t_ctx.out(),
            "|{0}|{0}|{0}|{0}|\n {1}|{1}|\n {1}|{1}|\n",
            fill_lower,
            fill_blank
        );
        return fmt::format_to(
            t_ctx.out(),
            " {0}|{1:^8s}|\n {0}|{2}|\n",
            fill_blank,
            color_scheme[t_cube_symm[CubeFace::FRONT]],
            fill_lower
        );
    }
};

constexpr CubeSymmetry identity{
    {{CubeFace::UP,
      CubeFace::DOWN,
      CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::FRONT,
      CubeFace::BACK}}};

constexpr CubeSymmetry x_ccw{
    {{CubeFace::BACK,
      CubeFace::FRONT,
      CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::UP,
      CubeFace::DOWN}}};
constexpr CubeSymmetry y_ccw{
    {{CubeFace::UP,
      CubeFace::DOWN,
      CubeFace::FRONT,
      CubeFace::BACK,
      CubeFace::LEFT,
      CubeFace::RIGHT}}};

constexpr CubeSymmetry z_ccw{
    {{CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::DOWN,
      CubeFace::UP,
      CubeFace::FRONT,
      CubeFace::BACK}}};

inline CubeSymmetry operator*(const CubeSymmetry& t_cube_symm, const int& t_n) {
    CubeSymmetry result = identity;
    if (t_n < 0) {
        for (int i = 0; i > (t_n % 4); --i) { result = result & -t_cube_symm; }
    } else {
        for (int i = 0; i < (t_n % 4); ++i) { result = result & t_cube_symm; }
    }
    return result;
}

inline CubeSymmetry operator*(const int& t_n, const CubeSymmetry& t_cube_symm) {
    return t_cube_symm * t_n;
}
#endif
