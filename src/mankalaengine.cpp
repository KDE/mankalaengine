/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <mankalaengine.h>

namespace MankalaEngine {

bool MankalaEngine::play(Player player, const Rules& rules, Board& state) {
    if (rules.gameOver(player, state)) {
        const Player winner = player == player_1 ? player_2 : player_1;
        rules.finishGame(winner, state);
        return false;
    }
    const int move = _selectMove(player, rules, state);
    rules.move(move, player, state);
    return true;
}

} // namespace MankalaEngine
