/*
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>
    SPDX-FileCopyrightText: 2025 Benson Muite <benson_muite@emailplus.org>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "kalahrules.h"

#include "rules.h"
#include "variantdescriptions.h"

// C++
#include <memory>
#include <utility>

namespace MankalaEngine {

struct KalahRules::KalahRulesImpl {
    bool is_opponents_hole(int pos, Player player) const {
        return (player == player_1 && pos >= 6 && pos < 12) ||
               (player == player_2 && pos >= 0 && pos < 6);
    }

    void try_capture(int pos, Player player, Board& state) const {
        if (state.holes.at(pos) != 1) {
            return;
        }
        state.stores.at(player) +=
            state.holes.at(11 - pos) + state.holes.at(pos);
        state.holes.at(11 - pos) = 0;
        state.holes.at(pos) = 0;
    }
};

KalahRules::KalahRules() : Rules(6, kalahDescription()) {}

void KalahRules::move(int pos, Player player, Board& state) const {
    const int max_index = player_holes() * 2 - 1;
    const int starting_position = position(pos, player);
    int current_position = starting_position;
    int pebbles = state.holes.at(current_position);
    bool own_kalah_last = false;

    // Picking up all pebbles in the hole
    state.holes.at(current_position) = 0;
    while (pebbles > 0) {
        if (++current_position > max_index) {
            current_position = 0;
        }
        // Check if need to drop in own kalah
        if (current_position == ((player == player_1) ? 6 : 0)) {
            state.stores.at(player) += 1;
            if (--pebbles == 0) {
                own_kalah_last = true;
            }
        }
        if (pebbles > 0) {
            // Skip starting position when sowing wraps around
            if (current_position == starting_position) {
                current_position++;
                if (current_position > max_index) {
                    current_position = 0;
                }
            }
            state.holes.at(current_position) += 1;
            pebbles--;
        }
    }
    if (!own_kalah_last) {
        // Capture, if possible, the pebbles in final position
        _impl->try_capture(current_position, player, state);
    }
}

bool KalahRules::isGameOver(Player player, const Board& state) const {
    return state.stores.at(player) > 36 || Rules::isGameOver(player, state);
}

bool KalahRules::isValidMove(int pos, Player player, const Board& state) const {
    if (pos >= player_holes() || pos < 0) {
        return false;
    }
    return state.holes.at(position(pos, player)) != 0;
}

KalahRules::KalahRules(KalahRules&& other) noexcept
    : Rules(6, kalahDescription()), _impl(std::move(other._impl)) {}

KalahRules& KalahRules::operator=(const KalahRules& other) {
    return *this = KalahRules(other);
}

KalahRules::KalahRules(const KalahRules& other)
    : Rules(6, kalahDescription()),
      _impl(std::make_unique<KalahRulesImpl>(*other._impl)) {}

KalahRules& KalahRules::operator=(KalahRules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

KalahRules::~KalahRules() = default;

} // namespace MankalaEngine
