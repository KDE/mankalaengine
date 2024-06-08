#include <rules.h>

namespace MankalaEngine {

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
