/*
    SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "pallangulirules.h"

#include "rules.h"
#include "variantdescriptions.h"

// C++
#include <memory>
#include <utility>

namespace MankalaEngine {

struct PallanguliRules::PallanguliRulesImpl {
    void recursive_move(int current_position, Player player, Board& state,
                        int max_index) const {
        int pebbles = state.holes.at(current_position);
        // Picking up all counters in the selected pit
        state.holes.at(current_position) = 0;

        while (pebbles-- > 0) {
            // Advance to the next pit
            if (++current_position > max_index) {
                current_position = 0;
            }
            state.holes.at(current_position) += 1;

            // Check for immediate capture if the pit reaches 4 counters
            if (state.holes.at(current_position) == 4) {
                state.stores.at(player) += state.holes.at(current_position);
                state.holes.at(current_position) = 0;
            }
        }
        int next_position = 0;
        int next2_position = 0;
        if (++current_position > max_index) {
            next_position = 0;
            next2_position = 1;
        } else {
            next_position = current_position;
            if (next_position + 1 > max_index) {
                next2_position = 0;
            } else {
                next2_position = next_position + 1;
            }
        }
        // check for termination
        if (state.holes.at(next_position) == 0 &&
            state.holes.at(next2_position) == 0) {
            return;
        }
        // check for Capture
        if (state.holes.at(next_position) == 0 &&
            state.holes.at(next2_position) > 0) {
            state.stores.at(player) += state.holes.at(next2_position);
            state.holes.at(next2_position) = 0;
        }
        // check for Continue
        else if (state.holes.at(next_position) > 0) {
            recursive_move(next_position, player, state, max_index);
        }
    }
};

PallanguliRules::PallanguliRules() : Rules(7, pallanguliDescription()) {}

void PallanguliRules::move(int move, Player player, Board& state) const {
    const int max_index = player_holes() * 2 - 1;
    int const current_position = position(move, player);

    _impl->recursive_move(current_position, player, state, max_index);
}

bool PallanguliRules::isValidMove(int move, Player player,
                                  const Board& state) const {
    if (move >= player_holes() || move < 0) {
        return false;
    }
    return state.holes.at(position(move, player)) != 0;
}

PallanguliRules::PallanguliRules(PallanguliRules&& other) noexcept
    : Rules(6, pallanguliDescription()), _impl(std::move(other._impl)) {}

PallanguliRules& PallanguliRules::operator=(const PallanguliRules& other) {
    return *this = PallanguliRules(other);
}

PallanguliRules::PallanguliRules(const PallanguliRules& other)
    : Rules(6, pallanguliDescription()),
      _impl(std::make_unique<PallanguliRulesImpl>(*other._impl)) {}

PallanguliRules& PallanguliRules::operator=(PallanguliRules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

PallanguliRules::~PallanguliRules() = default;

} // namespace MankalaEngine
