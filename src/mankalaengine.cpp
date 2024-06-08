#include <mankalaengine.h>

namespace MankalaEngine {

std::vector<int> MankalaEngine::getMoves(const Rules& rules, Player player,
                                         Board& state) {
    std::vector<int> moves;
    const int size = rules.player_holes();
    for (int i = 0; i < size; i++) {
        if (rules.validMove(i, player, state)) {
            moves.push_back(i);
        }
    }
    return moves;
}

bool MankalaEngine::play(const Rules& rules, Player player, Board& state) {
    const std::vector<int> moves = getMoves(rules, player, state);
    if (moves.empty()) {
        return false;
    }
    const int move = _selectMove(moves, state);
    rules.move(move, player, state);
    return true;
}

} // namespace MankalaEngine
