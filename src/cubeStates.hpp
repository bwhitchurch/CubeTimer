#ifndef CUBE_STATES_HPP
#define CUBE_STATES_HPP
#include "cube.hpp"    // for CubeFace, numCubeFaces
#include "enum.hpp"    // for BiEnum

#include <algorithm>   // for equal
#include <array>       // for array, operator==
#include <cstddef>     // for size_t
#include <fmt/core.h>  // for format_parse_context, formatter
#include <string_view> // for string_view

struct CubeSymmetry {
	std::array< CubeFace, numCubeFaces > m_state;

	CubeSymmetry operator&(const CubeSymmetry& other) const {
		CubeSymmetry result{};
		for (size_t i = 0; i < numCubeFaces; ++i) {
			result[i] = (*this)[other[i]];
		}
		return result;
	}

	CubeSymmetry operator-() const {
		CubeSymmetry result{};
		for (size_t i = 0; i < numCubeFaces; ++i) {
			result[m_state.at(i)] = CubeFace(i);
		}
		return result;
	}

	bool operator==(const CubeSymmetry& other) const {
		return m_state == other.m_state;
	}

	constexpr CubeFace operator[](const CubeFace& face) const {
		return m_state.at(static_cast< size_t >(face));
	}

	constexpr CubeFace operator[](const size_t& i) const {
		return m_state.at(i);
	}

	CubeFace& operator[](const CubeFace& face) {
		return m_state.at(static_cast< size_t >(face));
	}

	CubeFace& operator[](const size_t& i) { return m_state.at(i); }
};

constexpr BiEnum< CubeFace, std::string_view, numCubeFaces > colorScheme{
	{{{CubeFace::UP, "White"},
      {CubeFace::DOWN, "Yellow"},
      {CubeFace::RIGHT, "Red"},
      {CubeFace::LEFT, "Orange"},
      {CubeFace::FRONT, "Green"},
      {CubeFace::BACK, "Blue"}}}

};

template <> struct fmt::formatter< CubeSymmetry > {
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
		return ctx.end();
	}

	template < typename FormatContext >
	auto format(const CubeSymmetry& cubeSymm, FormatContext& ctx) const
		-> decltype(ctx.out()) {
		constexpr std::string_view fill_blank = "        ";
		constexpr std::string_view fill_upper = "‾‾‾‾‾‾‾‾";
		constexpr std::string_view fill_lower = "________";
		fmt::format_to(
			ctx.out(),
			"\n {0}|{1}|\n {0}|{0}|\n {0}|{2:^8s}|\n {0}|{0}|\n",
			fill_blank,
			fill_upper,
			colorScheme[cubeSymm[CubeFace::BACK]]
		);

		fmt::format_to(
			ctx.out(),
			"|{0}|{0}|{0}|{0}|\n|{1}|{1}|{1}|{1}|\n",
			fill_upper,
			fill_blank
		);
		fmt::format_to(
			ctx.out(),
			"|{0:^8s}|{1:^8s}|{2:^8s}|{3:^8s}|\n",
			colorScheme[cubeSymm[CubeFace::LEFT]],
			colorScheme[cubeSymm[CubeFace::UP]],
			colorScheme[cubeSymm[CubeFace::RIGHT]],
			colorScheme[cubeSymm[CubeFace::DOWN]]
		);
		fmt::format_to(
			ctx.out(),
			"|{0}|{0}|{0}|{0}|\n {1}|{1}|\n {1}|{1}|\n",
			fill_lower,
			fill_blank
		);
		return fmt::format_to(
			ctx.out(),
			" {0}|{1:^8s}|\n {0}|{2}|\n",
			fill_blank,
			colorScheme[cubeSymm[CubeFace::FRONT]],
			fill_lower
		);
	}
};

constexpr CubeSymmetry Identity{
	{{CubeFace::UP,
      CubeFace::DOWN,
      CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::FRONT,
      CubeFace::BACK}}};

constexpr CubeSymmetry X_CCW{
	{{CubeFace::BACK,
      CubeFace::FRONT,
      CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::UP,
      CubeFace::DOWN}}};
constexpr CubeSymmetry Y_CCW{
	{{CubeFace::UP,
      CubeFace::DOWN,
      CubeFace::FRONT,
      CubeFace::BACK,
      CubeFace::LEFT,
      CubeFace::RIGHT}}};

constexpr CubeSymmetry Z_CCW{
	{{CubeFace::RIGHT,
      CubeFace::LEFT,
      CubeFace::DOWN,
      CubeFace::UP,
      CubeFace::FRONT,
      CubeFace::BACK}}};

CubeSymmetry operator*(const CubeSymmetry& cubeSymm, const int& N) {
	if (N < 0) {
		return -cubeSymm * (-N);
	} else {
		CubeSymmetry result = Identity;
		for (int i = 0; i < (N % 4); ++i) { result = result & cubeSymm; }
		return result;
	}
}

CubeSymmetry operator*(const int& N, const CubeSymmetry& cubeSymm) {
	return cubeSymm * N;
}
#endif
