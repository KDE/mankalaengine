#include <cstdlib>
#include <moveselection.h>

namespace MankalaEngine {

int random(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }
    return moves.at(std::rand() % moves.size());
}

} // namespace MankalaEngine
