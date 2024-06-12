#include <rules.h>

namespace MankalaEngine {

void Rules::finishGame(Player winner, Board& state) const {
    int pebbles = 0;
    for (int i = 0; i < _player_holes; i++) {
        const int pos = position(i, winner);
        pebbles += state.holes.at(pos);
        state.holes.at(pos) = 0;
    }
    state.stores.at(winner) += pebbles;
}

bool Rules::gameOver(Player player, const Board& state) const {
    for (int i = 0; i < _player_holes; i++) {
        if (validMove(i, player, state)) {
            return false;
        }
    }
    return true;
}

std::vector<int> Rules::getMoves(Player player, const Board& state) const {
    std::vector<int> moves;
    for (int i = 0; i < _player_holes; i++) {
        if (validMove(i, player, state)) {
            moves.push_back(i);
        }
    }
    return moves;
}

} // namespace MankalaEngine
