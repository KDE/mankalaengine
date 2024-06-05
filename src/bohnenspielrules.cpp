#include <bohnenspielrules.h>

namespace MankalaEngine {

void BohnenspielRules::try_capture(int position, Player player,
                                   Board &state) const {

    int max_index = player_holes() * 2 - 1;
    int pebbles = state.holes.at(position);
    // Capture is only possible if the pebbles in the hole are 2, 4 or 6
    while (pebbles % 2 == 0 && pebbles < 7 && pebbles > 0) {
        // Capturing
        state.stores.at(player) += state.holes.at(position);
        state.holes.at(position) = 0;

        // Advance to the next position
        if (++position > max_index) {
            position = 0;
        }
        pebbles = state.holes.at(position);
    }
}

void BohnenspielRules::move(int move, Player player, Board &state) const {
    if (!validMove(move, player, state)) {
        return;
    }

    int current_position = position(move, player);
    int pebbles = state.holes.at(current_position);
    int max_index = player_holes() * 2 - 1;

    // Picking up all pebbles in the hole
    state.holes.at(current_position) = 0;
    while (pebbles-- > 0) {
        if (++current_position > max_index) {
            current_position = 0;
        }
        state.holes.at(current_position) += 1;
    }
    // Capture, if possible, the pebbles in final position
    try_capture(current_position, player, state);
}

bool BohnenspielRules::validMove(int move, Player player,
                                 const Board &state) const {

    if (move >= player_holes() || move < 0) {
        return false;
    }
    return state.holes.at(position(move, player)) != 0;
}

} // namespace MankalaEngine
