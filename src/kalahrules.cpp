/*
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <kalahrules.h>
#include <memory>
#include <rules.h>
#include <utility>
#include <variantdescriptions.h>

namespace MankalaEngine {

struct KalahRules::KalahRulesImpl {
    bool is_opponents_hole(int pos, Player player) const {
        return (player == player_1 && pos > 7 && pos < 14) ||
               (player == player_2 && pos > 0 && pos < 7);
    }

    bool is_opponents_kalah(int pos, Player player) const {
        return (player == player_1 && pos == 0) ||
               (player ==  player_2 && pos == 7);
    }

    bool opponent_has_pebbles(Player player, const Board& state) const {
        const int finish = player == player_1 ? 14 : 7;
        for (int i = player == player_1 ? 8 : 1; i < finish; ++i) {
            if (state.holes.at(i) != 0) {
                return true;
            }
        }
        return false;
    }

    void try_capture(int pos, Player player, Board& state) const {
        if (pos == 0 || pos == 7) {return;}
        if (state.holes.at(pos) != 1) {return;}
        state.stores.at(player) += state.holes.at(13-pos) + state.holes.at(pos);
        state.holes.at(13-pos) = 0;
        state.holes.at(pos) = 0;
    }

};

KalahRules::KalahRules() : Rules(7, KALAH_DESCRIPTION) {}

void KalahRules::move(int pos, Player player, Board& state) const {
    const int max_index = player_holes() * 2 - 1;
    const int starting_position = position(pos, player);
    int current_position = starting_position;
    int pebbles = state.holes.at(current_position);

    // Picking up all pebbles in the hole
    state.holes.at(current_position) = 0;
    while (pebbles > 0) {
        if (++current_position > max_index) {
            current_position = 0;
        }
        // Skip starting position when sowing wraps around
        if (current_position != starting_position && !_impl->is_opponents_kalah(current_position, player)) {
            --pebbles;
            state.holes.at(current_position) += 1;
        }
    }
    state.stores.at(player) = state.holes.at(player==player_1?7:0);

    // Capture, if possible, the pebbles in final position
    _impl->try_capture(current_position, player, state);

    // Sync board store
    state.holes.at(player == player_1? 7 : 0) = state.stores.at(player);
}

bool KalahRules::isGameOver(Player player, const Board& state) const {
    return state.stores.at(player)>36 || Rules::isGameOver(player, state);
}

bool KalahRules::isValidMove(int pos, Player player, const Board& state) const {
    if (pos >= player_holes() || pos < 0 ||
        state.holes.at(position(pos, player)) == 0) {
        return false;
    }
    Board new_state = state;
    move(pos, player, new_state);
    return _impl->opponent_has_pebbles(player, new_state);
}

void KalahRules::finishGame(Player player, Board& state) const {
    // finishGame assumes the player whose turn ends the game is the loser, but
    // in Kalah, it's actually the opposite
    const Player flipped_player = player == player_1 ? player_2 : player_1;
    Rules::finishGame(flipped_player, state);
}


KalahRules::KalahRules(KalahRules&& other) noexcept
    : Rules(7, KALAH_DESCRIPTION), _impl(std::move(other._impl)) {}

KalahRules& KalahRules::operator=(const KalahRules& other) {
    return *this = KalahRules(other);
}

KalahRules::KalahRules(const KalahRules& other)
    : Rules(7, KALAH_DESCRIPTION),
      _impl(std::make_unique<KalahRulesImpl>(*other._impl)) {}

KalahRules& KalahRules::operator=(KalahRules&& other) noexcept {
    std::swap(_impl, other._impl);
    return *this;
}

KalahRules::~KalahRules() = default;

}
