/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "rules.h"

#include "variantdescriptions.h"

// C++
#include <memory>
#include <utility>
#include <vector>

// Qt
#include <QtCore/QString>

namespace MankalaEngine {

struct Rules::RulesImpl {
    // Allow non private member variables, since the whole class is private.
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    int _player_holes;
    QString _description;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    RulesImpl(int player_holes, QString description)
        : _player_holes(player_holes), _description(std::move(description)) {}
};

Rules::Rules(int player_holes)
    : _impl(std::make_unique<RulesImpl>(player_holes,
                                        placeholderDescription())) {}

Rules::Rules(int player_holes, QString description)
    : _impl(std::make_unique<RulesImpl>(player_holes, std::move(description))) {
}

int Rules::player_holes() const { return _impl->_player_holes; }

QString Rules::description() const { return _impl->_description; }

void Rules::finishGame(Player player, Board& state) const {
    const Player winner = player == player_1 ? player_2 : player_1;
    for (int i = 0; i < _impl->_player_holes; i++) {
        const int pos = position(i, winner);
        state.stores.at(winner) += state.holes.at(pos);
        state.holes.at(pos) = 0;
    }
}

bool Rules::isGameOver(Player player, const Board& state) const {
    for (int i = 0; i < _impl->_player_holes; i++) {
        if (isValidMove(i, player, state)) {
            return false;
        }
    }
    return true;
}

std::vector<int> Rules::getMoves(Player player, const Board& state) const {
    std::vector<int> moves;
    for (int i = 0; i < _impl->_player_holes; i++) {
        if (isValidMove(i, player, state)) {
            moves.push_back(i);
        }
    }
    return moves;
}

Rules::Rules(Rules&& other) noexcept : _impl(std::move(other._impl)) {}

// Fix in a separate step for clang-tidy 20
// NOLINTBEGIN(bugprone-unhandled-self-assignment)
Rules& Rules::operator=(const Rules& other) {
    _impl = std::make_unique<RulesImpl>(*other._impl);
    return *this;
}

Rules::Rules(const Rules& other)
    : _impl(std::make_unique<RulesImpl>(*other._impl)) {}

Rules& Rules::operator=(Rules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}
// NOLINTEND(bugprone-unhandled-self-assignment)

Rules::~Rules() = default;

} // namespace MankalaEngine
