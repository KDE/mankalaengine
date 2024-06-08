#include <mankalaengine.h>

namespace MankalaEngine {

bool MankalaEngine::play(const Rules& rules, Player player, Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return false;
    }
    const int move = _selectMove(moves, state);
    rules.move(move, player, state);
    return true;
}

} // namespace MankalaEngine
