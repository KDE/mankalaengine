/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "owarerules.h"

#include "rules.h"
#include "variantdescriptions.h"

// C++
#include <array>
#include <memory>
#include <utility>

namespace MankalaEngine {

struct OwareRules::OwareRulesImpl {
    bool is_opponents_hole(int position, Player player) const {
        return (player == player_1 && position > 5 && position < 12) ||
               (player == player_2 && position > -1 && position < 6);
    }

    bool opponent_has_pebbles(Player player, const Board& state) const {
        const int finish = player == player_1 ? 12 : 6;
        for (int i = player == player_1 ? 6 : 0; i < finish; ++i) {
            if (state.holes.at(i) != 0) {
                return true;
            }
        }
        return false;
    }

    void try_capture(int position, Player player, Board& state) const {
        Board new_state = state;
        int pebbles = new_state.holes.at(position);
        // Capture is only possible if the pebbles in the hole are 2 or 3
        while ((pebbles == 2 || pebbles == 3) &&
               is_opponents_hole(position, player)) {
            // Capturing
            new_state.stores.at(player) += new_state.holes.at(position);
            new_state.holes.at(position) = 0;

            // Go to the preceding hole
            if (--position < 0) {
                break;
            }
            pebbles = new_state.holes.at(position);
        }

        // Checking for a Grand Slam
        if (opponent_has_pebbles(player, new_state)) {
            std::swap(state, new_state);
        }
    }
};

OwareRules::OwareRules() : Rules(6, owareDescription()) {}

void OwareRules::move(int move, Player player, Board& state) const {
    const int max_index = player_holes() * 2 - 1;
    const int starting_position = position(move, player);
    int current_position = starting_position;
    int pebbles = state.holes.at(current_position);

    // Picking up all pebbles in the hole
    state.holes.at(current_position) = 0;
    while (pebbles > 0) {
        if (++current_position > max_index) {
            current_position = 0;
        }
        // Skip starting position when sowing wraps around
        if (current_position != starting_position) {
            --pebbles;
            state.holes.at(current_position) += 1;
        }
    }

    // Capture, if possible, the pebbles in final position
    _impl->try_capture(current_position, player, state);
}

bool OwareRules::isGameOver(Player player, const Board& state) const {
    return state.stores.at(player) > 24 || Rules::isGameOver(player, state);
}

bool OwareRules::isValidMove(int pos, Player player, const Board& state) const {
    if (pos >= player_holes() || pos < 0 ||
        state.holes.at(position(pos, player)) == 0) {
        return false;
    }
    Board new_state = state;
    move(pos, player, new_state);
    return _impl->opponent_has_pebbles(player, new_state);
}

void OwareRules::finishGame(Player player, Board& state) const {
    // finishGame assumes the player whose turn ends the game is the loser, but
    // in Oware, it's actually the opposite
    const Player flipped_player = player == player_1 ? player_2 : player_1;
    Rules::finishGame(flipped_player, state);
}

OwareRules::OwareRules(OwareRules&& other) noexcept
    : Rules(6, owareDescription()), _impl(std::move(other._impl)) {}

OwareRules& OwareRules::operator=(const OwareRules& other) {
    return *this = OwareRules(other);
}

OwareRules::OwareRules(const OwareRules& other)
    : Rules(6, owareDescription()),
      _impl(std::make_unique<OwareRulesImpl>(*other._impl)) {}

OwareRules& OwareRules::operator=(OwareRules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

OwareRules::~OwareRules() = default;

} // namespace MankalaEngine
