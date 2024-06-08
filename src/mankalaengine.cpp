#include <mankalaengine.h>

namespace MankalaEngine {

bool MankalaEngine::play(Player player, const Rules& rules, Board& state) {
    if (rules.gameOver(player, state)) {
        return false;
    }
    const int move = _selectMove(player, rules, state);
    rules.move(move, player, state);
    return true;
}

} // namespace MankalaEngine
