/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "mankalaengine_export.h"
#include "rules.h"

// C++
#include <limits>
#include <memory>
#include <unordered_map>

namespace MankalaEngine {

constexpr int N_INFINITY = std::numeric_limits<int>::min();
constexpr int P_INFINITY = std::numeric_limits<int>::max();

struct MANKALAENGINE_NO_EXPORT SearchResult {
    int move = -1;
    int eval = 0;
};

struct MANKALAENGINE_NO_EXPORT NodeScore {
    int lowerbound = N_INFINITY;
    int upperbound = P_INFINITY;
    int move = -1;
};

using Table = std::unordered_map<unsigned int, std::unique_ptr<NodeScore>>;

MANKALAENGINE_NO_EXPORT bool _greater(int x, int y);

MANKALAENGINE_NO_EXPORT bool _less(int x, int y);

MANKALAENGINE_NO_EXPORT unsigned int _hash(Player player, const Board& state);

MANKALAENGINE_NO_EXPORT int _eval(const Board& state);

MANKALAENGINE_NO_EXPORT SearchResult _alphaBeta(Player player,
                                                const Rules& rules,
                                                const Board& state, int depth,
                                                int alpha, int beta,
                                                Table& table);

MANKALAENGINE_NO_EXPORT SearchResult _mtdf(Player player, const Rules& rules,
                                           const Board& state, int first_guess,
                                           int depth, Table& table);

MANKALAENGINE_EXPORT int user(Player player, const Rules& rules,
                              const Board& state);

MANKALAENGINE_EXPORT int random(Player player, const Rules& rules,
                                const Board& state);

MANKALAENGINE_EXPORT int miniMax(Player player, const Rules& rules,
                                 const Board& state);

MANKALAENGINE_EXPORT int mtdf(Player player, const Rules& rules,
                              const Board& state);

MANKALAENGINE_EXPORT int greedy(Player player, const Rules& rules,
                                const Board& state);

} // namespace MankalaEngine
