/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mankalaengine.h"

#include "rules.h"

// C++
#include <cassert>
#include <functional>
#include <memory>
#include <utility>

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
        rules.finishGame(player, state);
        return false;
    }
    const int move = _impl->_selectMove(player, rules, state);

    assert(rules.isValidMove(move, player, state) &&
           "Move selection returned an invalid move.");

    rules.move(move, player, state);
    return true;
}

MankalaEngine::MankalaEngine(MankalaEngine&& other) noexcept
    : _impl(std::move(other._impl)) {}

MankalaEngine& MankalaEngine::operator=(const MankalaEngine& other) {
    return *this = MankalaEngine(other);
}

MankalaEngine::MankalaEngine(const MankalaEngine& other)
    : _impl(std::make_unique<MankalaEngineImpl>(*other._impl)) {}

MankalaEngine& MankalaEngine::operator=(MankalaEngine&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

MankalaEngine::~MankalaEngine() = default;

} // namespace MankalaEngine
