#include <mankalaengine.h>

namespace MankalaEngine {

bool MankalaEngine::play(Player player, const Rules& rules, Board& state) {
    const int move = _selectMove(player, rules, state);
    if (move == -1) {
        return false;
    }
    rules.move(move, player, state);
    return true;
}

} // namespace MankalaEngine
