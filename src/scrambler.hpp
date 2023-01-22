#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include <algorithm>  // for fill_n
#include <array>      // for array
#include <cstdlib>    // for size_t
#include <iostream>   // for operator<<, basic_ostream, stringstream, basic_...
#include <random>     // for mt19937, uniform_real_distribution, random_device
#include <string>     // for char_traits, allocator, string, getline
#include <sstream>

#include "cube.hpp"   // for num_cube_faces, CubeFace (ptr only), num_turns
#include "enum.hpp"   // for BiEnum

constexpr size_t default_scramble_length = 25;

class Scrambler {
	size_t                           m_length;
	std::mt19937                     m_gen;
	std::uniform_real_distribution<> m_dis;
    std::array< CubeFace, 2 >        m_state;

    std::array< double, num_cube_faces > m_computeTransitionProbs() {
        std::array< double, num_cube_faces > transition_probs{};
        if (cube_face_axis_pair[m_state[0]] != m_state[1]) {
            transition_probs.fill(1.0 / (num_cube_faces - 1));
            transition_probs.at(static_cast< size_t >(m_state[1])) = 0.0;
        } else {
            transition_probs.fill(1.0 / (num_cube_faces - 2));
            transition_probs.at(static_cast< size_t >(m_state[0])) = 0.0;
            transition_probs.at(static_cast< size_t >(m_state[1])) = 0.0;
        }
        double cum_sum = 0.0;
        for (auto& prob : transition_probs) {
            cum_sum += prob;
            prob = cum_sum;
        }

        return transition_probs;
    }

  public:
    Scrambler() : Scrambler(default_scramble_length) {}

    explicit Scrambler(const size_t& t_scramble_length)
        : m_length(t_scramble_length),
          m_gen(std::random_device{}()),
          m_dis(0.0, 1.0),
          m_state{} {
        std::array< double, num_cube_faces > state_prob{};
        state_prob.fill(1.0 / num_cube_faces);
        double sum = 0.0;
        for (auto& prob : state_prob) {
            sum += prob;
			prob = sum;
        }
        double rand_val = m_dis(m_gen);
        size_t idx       = 0;
        while (rand_val >= state_prob.at(idx)) { ++idx; }
        m_state[0] = CubeFace(idx);
        state_prob.fill(1.0 / (num_cube_faces - 1));
        state_prob.at(static_cast< size_t >(m_state[0])) = 0.0;
        sum                                             = 0.0;
        for (auto& prob : state_prob) {
            sum += prob;
			prob = sum;
        }
        idx       = 0;
        rand_val = m_dis(m_gen);
        while (rand_val > state_prob.at(idx)) { ++idx; }
        m_state[1] = CubeFace(idx);
    }

    std::string generateScramble() {
        size_t            moves_generated = 0;
        std::stringstream the_scramble{""};
        while (moves_generated < m_length) {
            if (moves_generated > 0) { the_scramble << " "; }
            auto         prob_table = m_computeTransitionProbs();
            const double rand_face  = m_dis(m_gen);
            size_t idx         = 0;
            while (rand_face > prob_table.at(idx)) { ++idx; }
            const auto curr_face    = CubeFace(idx);
            m_state[0]              = m_state[1];
            m_state[1]              = curr_face;
            the_scramble << cube_face_notation[curr_face];
            const double rand_turn = m_dis(m_gen);
            if (rand_turn < 1. / num_turns) {
                the_scramble << turn_notation[FaceTurn::ANTICLOCKWISE];
            } else if (rand_turn < 2. / num_turns) {
                the_scramble << turn_notation[FaceTurn::CLOCKWISE];
            } else {
                the_scramble << turn_notation[FaceTurn::HALFTURN];
            }
            ++moves_generated;
		}
        return the_scramble.str();
    }

    static void scrambleStats(
        const std::string&                                t_scramble,
        std::array< size_t, num_cube_faces * num_turns >& t_stats
    ) {
        std::stringstream scramble_stream(t_scramble);
        std::string       move;
        while (std::getline(scramble_stream, move, ' ')) {
            const CubeFace face = cube_face_notation[move[0]];
            const FaceTurn turn = turn_notation[move[1]];
            ++t_stats.at(
                num_turns * static_cast< size_t >(face)
                + static_cast< size_t >(turn)
            );
        }
    }
};

#endif
