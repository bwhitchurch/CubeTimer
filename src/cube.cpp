#include "cube.hpp"

#include <unordered_map>

const std::unordered_map< CubeFace, CubeFace >& getAxisPairs() {

    const static std::unordered_map< CubeFace, CubeFace > face_opposites{
        {   CubeFace::UP,  CubeFace::DOWN},
        { CubeFace::DOWN,    CubeFace::UP},
        {CubeFace::RIGHT,  CubeFace::LEFT},
        { CubeFace::LEFT, CubeFace::RIGHT},
        {CubeFace::FRONT,  CubeFace::BACK},
        { CubeFace::BACK, CubeFace::FRONT},
    };
    return face_opposites;
}
