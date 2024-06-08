#include <rules.h>

namespace MankalaEngine {

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
