/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "bohnenspielrules.h"

#include "rules.h"
#include "variantdescriptions.h"

// C++
#include <memory>
#include <utility>

namespace MankalaEngine {

struct BohnenspielRules::BohnenspielRulesImpl {
    void try_capture(int position, Player player, Board& state,
                     int max_index) const {
        int pebbles = state.holes.at(position);
        // Capture is only possible if the pebbles in the hole are 2, 4 or 6
        while (pebbles % 2 == 0 && pebbles < 7 && pebbles > 0) {
            // Capturing
            state.stores.at(player) += state.holes.at(position);
            state.holes.at(position) = 0;

            // Go to the preceding hole
            if (--position < 0) {
                position = max_index;
            }
            pebbles = state.holes.at(position);
        }
    }
};

BohnenspielRules::BohnenspielRules() : Rules(6, bohnenspielDescription()) {}

void BohnenspielRules::move(int move, Player player, Board& state) const {
    const int max_index = player_holes() * 2 - 1;
    int current_position = position(move, player);
    int pebbles = state.holes.at(current_position);

    // Picking up all pebbles in the hole
    state.holes.at(current_position) = 0;
    while (pebbles-- > 0) {
        if (++current_position > max_index) {
            current_position = 0;
        }
        state.holes.at(current_position) += 1;
    }
    // Capture, if possible, the pebbles in final position
    _impl->try_capture(current_position, player, state, max_index);
}

bool BohnenspielRules::isValidMove(int move, Player player,
                                   const Board& state) const {

    if (move >= player_holes() || move < 0) {
        return false;
    }
    return state.holes.at(position(move, player)) != 0;
}

BohnenspielRules::BohnenspielRules(BohnenspielRules&& other) noexcept
    : Rules(6, bohnenspielDescription()), _impl(std::move(other._impl)) {}

BohnenspielRules& BohnenspielRules::operator=(const BohnenspielRules& other) {
    return *this = BohnenspielRules(other);
}

BohnenspielRules::BohnenspielRules(const BohnenspielRules& other)
    : Rules(6, bohnenspielDescription()),
      _impl(std::make_unique<BohnenspielRulesImpl>(*other._impl)) {}

BohnenspielRules&
BohnenspielRules::operator=(BohnenspielRules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

BohnenspielRules::~BohnenspielRules() = default;

} // namespace MankalaEngine
