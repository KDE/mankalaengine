/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <mankalaengine.h>
#include <memory>

namespace MankalaEngine {

struct MankalaEngine::MankalaEngineImpl {
    // Allow non private member variables, since the whole class is private.
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    std::function<int(Player player, const Rules&, const Board&)> _selectMove;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    explicit MankalaEngineImpl(
        std::function<int(Player, const Rules&, const Board&)> selectMove)
        : _selectMove(std::move(selectMove)) {}
};

MankalaEngine::MankalaEngine(
    std::function<int(Player, const Rules&, const Board&)> selectMove)
    : _impl(std::make_unique<MankalaEngineImpl>(std::move(selectMove))) {}

bool MankalaEngine::play(Player player, const Rules& rules,
                         Board& state) const {
    if (rules.isGameOver(player, state)) {
        const Player winner = player == player_1 ? player_2 : player_1;
        rules.finishGame(winner, state);
        return false;
    }
    const int move = _impl->_selectMove(player, rules, state);
    rules.move(move, player, state);
    return true;
}

MankalaEngine::~MankalaEngine() = default;

} // namespace MankalaEngine
