#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include "cube.hpp"  // for num_cube_faces, CubeFace (ptr only), num_turns

#include <algorithm> // for fill_n
#include <array>     // for array
#include <cstdlib>   // for size_t
#include <iostream>  // for operator<<, basic_ostream, stringstream, basic_...
#include <random>    // for mt19937, uniform_real_distribution, random_device
#include <sstream>
#include <string>    // for char_traits, allocator, string, getline
#include <unordered_map>

constexpr size_t default_scramble_length = 25;

class Scrambler {
    size_t                           m_length;
    std::mt19937                     m_gen;
    std::uniform_real_distribution<> m_dis;
    std::array< CubeFace, 2 >        m_state;

    std::array< double, num_cube_faces > m_computeTransitionProbs() {
        std::array< double, num_cube_faces > transition_probs{};
        if (getAxisPairs().at(m_state[0]) != m_state[1]) {
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
          m_state({CubeFace::RIGHT, CubeFace::UP}) {
        std::array< double, CubeFace::size() > state_prob{};
        state_prob.fill(1.0 / num_cube_faces);
        double sum = 0.0;
        for (auto& prob : state_prob) {
            sum += prob;
            prob = sum;
        }
        double rand_val = m_dis(m_gen);
        size_t idx      = 0;
        while (rand_val >= state_prob.at(idx)) { ++idx; }
        m_state[0] = CubeFace::values()[idx];
        state_prob.fill(1.0 / (num_cube_faces - 1));
        state_prob.at(static_cast< size_t >(m_state[0])) = 0.0;
        sum                                              = 0.0;
        for (auto& prob : state_prob) {
            sum += prob;
            prob = sum;
        }
        idx      = 0;
        rand_val = m_dis(m_gen);
        while (rand_val > state_prob.at(idx)) { ++idx; }
        m_state[1] = CubeFace::values()[idx];
    }

    std::string generateScramble() {
        size_t                  moves_generated = 0;
        std::vector< CubeMove > the_scramble;
        the_scramble.reserve(m_length);
        while (moves_generated < m_length) {
            auto         prob_table = m_computeTransitionProbs();
            const double rand_face  = m_dis(m_gen);
            size_t       idx        = 0;
            while (rand_face > prob_table.at(idx)) { ++idx; }
            const auto curr_face   = CubeFace::values()[idx];
            m_state[0]             = m_state[1];
            m_state[1]             = curr_face;
            const double rand_turn = m_dis(m_gen);
            idx                    = 0;
            while (rand_turn > double(idx + 1) / 3) { ++idx; }
            const auto curr_turn =
                FaceTurn::values()[idx]; the_scramble.emplace_back(
                    curr_face, curr_turn
                );
            ++moves_generated;
        }
        return fmt::format("{}", fmt::join(the_scramble, " "));
    }

    static void scrambleStats(
        const std::string&                                t_scramble,
        std::array< size_t, num_cube_faces * num_turns >& t_stats
    ) {
        std::stringstream scramble_stream(t_scramble);
        std::string       move_str;
        while (std::getline(scramble_stream, move_str, ' ')) {
            const CubeMove move(move_str);
            ++t_stats.at(num_turns * move.face + move.turn);
        }
    }
};

#endif
