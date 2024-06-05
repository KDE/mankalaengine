#pragma once

#include <cstdlib>
#include <moveselection.h>

namespace MankalaEngine {

int random(const std::vector<int> &moves, Board &state) {
    return moves.at(std::rand() % moves.size());
}

} // namespace MankalaEngine
