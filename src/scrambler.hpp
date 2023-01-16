#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include "enum.hpp"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string_view>
#include <utility>

#include <sstream>

constexpr size_t numCubeFaces = 6;
enum class CubeFace { UP, DOWN, RIGHT, LEFT, FRONT, BACK };
constexpr BiEnum< CubeFace, char, numCubeFaces > cubeFaceNotation{
	{{{CubeFace::UP, 'U'},
      {CubeFace::DOWN, 'D'},
      {CubeFace::RIGHT, 'R'},
      {CubeFace::LEFT, 'L'},
      {CubeFace::FRONT, 'F'},
      {CubeFace::BACK, 'B'}}}};

constexpr size_t numTurns = 3;
enum class FaceTurn { ANTICLOCKWISE, CLOCKWISE, HALFTURN };
constexpr BiEnum< FaceTurn, char, numTurns > turnNotation{
	{{{FaceTurn::ANTICLOCKWISE, '\''},
      {FaceTurn::CLOCKWISE, '\0'},
      {FaceTurn::HALFTURN, '2'}}}};

constexpr std::array< std::pair< CubeFace, CubeFace >, numCubeFaces >
	cubeFaceAxisPair{
		{{CubeFace::UP, CubeFace::DOWN},
         {CubeFace::DOWN, CubeFace::UP},
         {CubeFace::RIGHT, CubeFace::LEFT},
         {CubeFace::LEFT, CubeFace::RIGHT},
         {CubeFace::FRONT, CubeFace::BACK},
         {CubeFace::BACK, CubeFace::FRONT}}
};

constexpr CubeFace axisPartner(const CubeFace& face) {
	const auto* found = std::find_if(
		cubeFaceAxisPair.begin(),
		cubeFaceAxisPair.end(),
		[face](const auto& itVal) { return itVal.first == face; }
	);
	return found->second;
}

static_assert(axisPartner(CubeFace::UP) == CubeFace::DOWN);
static_assert(axisPartner(CubeFace::DOWN) == CubeFace::UP);
static_assert(axisPartner(CubeFace::RIGHT) == CubeFace::LEFT);
static_assert(axisPartner(CubeFace::LEFT) == CubeFace::RIGHT);
static_assert(axisPartner(CubeFace::FRONT) == CubeFace::BACK);
static_assert(axisPartner(CubeFace::BACK) == CubeFace::FRONT);

constexpr size_t default_scramble_length = 25;

class Scrambler {
	size_t                           m_length;
	std::mt19937                     m_gen;
	std::uniform_real_distribution<> m_dis;
	std::array< CubeFace, 2 >        m_state;

	std::array< double, numCubeFaces > computeTransitionProbs() {
		std::array< double, numCubeFaces > transitionProbs{};
		if (axisPartner(m_state[0]) != m_state[1]) {
			transitionProbs.fill(1.0 / (numCubeFaces - 1));
			transitionProbs.at(static_cast< size_t >(m_state[1])) = 0.0;
		} else {
			transitionProbs.fill(1.0 / (numCubeFaces - 2));
			transitionProbs.at(static_cast< size_t >(m_state[0])) = 0.0;
			transitionProbs.at(static_cast< size_t >(m_state[1])) = 0.0;
		}
		double cumSum = 0.0;
		for (auto& prob : transitionProbs) {
			cumSum += prob;
			prob = cumSum;
		}

		return transitionProbs;
	}

  public:
	Scrambler() : Scrambler(default_scramble_length) {}

	explicit Scrambler(const size_t& scramble_length)
		: m_length(scramble_length),
		  m_gen(std::random_device{}()),
		  m_dis(0.0, 1.0),
		  m_state{} {
		std::array< double, numCubeFaces > stateProb{};
		stateProb.fill(1.0 / numCubeFaces);
		double sum = 0.0;
		for (auto& prob : stateProb) {
			sum += prob;
			prob = sum;
		}
		double randVal = m_dis(m_gen);
		size_t i       = 0;
		while (randVal >= stateProb.at(i)) { ++i; }
		m_state[0] = CubeFace(i);
		stateProb.fill(1.0 / (numCubeFaces - 1));
		stateProb.at(static_cast< size_t >(m_state[0])) = 0.0;
		sum                                             = 0.0;
		for (auto& prob : stateProb) {
			sum += prob;
			prob = sum;
		}
		i       = 0;
		randVal = m_dis(m_gen);
		while (randVal > stateProb.at(i)) { ++i; }
		m_state[1] = CubeFace(i);
	}

	std::string generate_scramble() {
		size_t            moves_generated = 0;
		std::stringstream theScramble;
		while (moves_generated < m_length) {
			if (moves_generated > 0) { theScramble << " "; }
			auto   probTable = computeTransitionProbs();
			double randFace  = m_dis(m_gen);
			size_t i         = 0;
			while (randFace > probTable.at(i)) { ++i; }
			const CubeFace currFace = CubeFace(i);
			m_state[0]              = m_state[1];
			m_state[1]              = currFace;
			theScramble << cubeFaceNotation[currFace];
			double randTurn = m_dis(m_gen);
			if (randTurn < 1.0 / 3.0) {
				theScramble << turnNotation[FaceTurn::ANTICLOCKWISE];
			} else if (randTurn < 2.0 / 3.0) {
				theScramble << turnNotation[FaceTurn::CLOCKWISE];
			} else {
				theScramble << turnNotation[FaceTurn::HALFTURN];
			}
			++moves_generated;
		}
		return theScramble.str();
	}

	static void scramble_stats(
		const std::string&                             scramble,
		std::array< size_t, numCubeFaces * numTurns >& stats
	) {
		std::stringstream scrambleStream(scramble);
		std::string       move;
		while (std::getline(scrambleStream, move, ' ')) {
			const CubeFace face = cubeFaceNotation[move[0]];
			const FaceTurn turn = turnNotation[move[1]];
			++stats.at(
				numTurns * static_cast< size_t >(face)
				+ static_cast< size_t >(turn)
			);
		}
	}
};

#endif
