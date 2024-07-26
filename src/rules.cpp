/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include <memory>
#include <rules.h>
#include <variantdescriptions.h>

namespace MankalaEngine {

struct Rules::RulesImpl {
    // Allow non private member variables, since the whole class is private.
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    int _player_holes;
    std::string _description;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    RulesImpl(int player_holes, std::string description)
        : _player_holes(player_holes), _description(std::move(description)) {}
};

Rules::Rules(int player_holes)
    : _impl(
          std::make_unique<RulesImpl>(player_holes, PLACEHOLDER_DESCRIPTION)) {}

Rules::Rules(int player_holes, std::string description)
    : _impl(std::make_unique<RulesImpl>(player_holes, std::move(description))) {
}

int Rules::player_holes() const { return _impl->_player_holes; }

const std::string& Rules::description() const { return _impl->_description; }

void Rules::finishGame(Player winner, Board& state) const {
    int pebbles = 0;
    for (int i = 0; i < _impl->_player_holes; i++) {
        const int pos = position(i, winner);
        pebbles += state.holes.at(pos);
        state.holes.at(pos) = 0;
    }
    state.stores.at(winner) += pebbles;
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

Rules::~Rules() = default;

} // namespace MankalaEngine
