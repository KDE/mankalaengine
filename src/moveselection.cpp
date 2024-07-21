/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <moveselection.h>
#include <random>
#include <unordered_map>

namespace MankalaEngine {

constexpr int N_INFINITY = std::numeric_limits<int>::min();
constexpr int P_INFINITY = std::numeric_limits<int>::max();

struct SearchResult {
    int move = -1;
    int eval = 0;
};

struct NodeScore {
    int lowerbound = N_INFINITY;
    int upperbound = P_INFINITY;
    int move = -1;
};

using Table = std::unordered_map<int, std::unique_ptr<NodeScore>>;

bool _greater(int x, int y) { return x > y; }

bool _less(int x, int y) { return x < y; }

int _hash(Player player, const Board& state) {
    int hash = player;
    for (auto x : state.holes) {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        hash ^= x + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

int _eval(const Board& state) {
    return state.stores.at(player_1) - state.stores.at(player_2);
}

SearchResult _alphaBeta(Player player, const Rules& rules, const Board& state,
                        int depth, int alpha, int beta, Table& table) {

    SearchResult result;
    const int hash = _hash(player, state);
    auto emplace_result = table.emplace(hash, std::make_unique<NodeScore>());
    const auto entry = emplace_result.first;

    if (!emplace_result.second) { // Emplace failed, entry already exists
        result.move = entry->second->move;

        if (entry->second->lowerbound >= beta) {
            result.eval = entry->second->lowerbound;
            return result;
        }
        if (entry->second->upperbound <= alpha) {
            result.eval = entry->second->upperbound;
            return result;
        }

        alpha = std::max(alpha, entry->second->lowerbound);
        beta = std::min(beta, entry->second->upperbound);
    }

    if (depth == 0 || rules.gameOver(player, state)) { // Leaf node
        result.eval = _eval(state);
    } else if (player == player_1) { // Max node
        int a = alpha;
        result.eval = N_INFINITY;

        Board new_state = state;
        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            const int eval = _alphaBeta(player_2, rules, new_state, depth - 1,
                                        a, beta, table)
                                 .eval;

            if (eval > result.eval) {
                result.eval = eval;
                result.move = move;
            }

            if (result.eval >= beta) {
                break;
            }

            a = std::max(a, result.eval);
            new_state = state; // Undo previous move
        }
    } else { // Min node
        int b = beta;
        result.eval = P_INFINITY;

        Board new_state = state;
        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            const int eval = _alphaBeta(player_1, rules, new_state, depth - 1,
                                        alpha, b, table)
                                 .eval;

            if (eval < result.eval) {
                result.eval = eval;
                result.move = move;
            }

            if (result.eval <= alpha) {
                break;
            }

            b = std::min(b, result.eval);
            new_state = state; // Undo previous move
        }
    }

    entry->second->move = result.move;

    if (result.eval <= alpha) {
        entry->second->lowerbound = result.eval;
    }
    if (result.eval > alpha && result.eval < beta) {
        entry->second->lowerbound = result.eval;
        entry->second->upperbound = result.eval;
    }
    if (result.eval >= beta) {
        entry->second->upperbound = result.eval;
    }
    return result;
}

SearchResult _mtdf(Player player, const Rules& rules, const Board& state,
                   int first_guess, int depth, Table& table) {
    int beta;
    int upperbound = P_INFINITY;
    int lowerbound = N_INFINITY;
    SearchResult result;

    result.eval = first_guess;
    do {
        beta = result.eval == lowerbound ? result.eval + 1 : result.eval;
        result = _alphaBeta(player, rules, state, depth, beta - 1, beta, table);
        if (result.eval < beta) {
            upperbound = result.eval;
        } else {
            lowerbound = result.eval;
        }
    } while (lowerbound < upperbound);
    return result;
}

int user(Player player, const Rules& rules, const Board& state) {
    int move = -1;
    std::cin >> move;
    while (!rules.validMove(move, player, state)) {
        std::cout << "Please provide a valid move.\n";
        std::cin >> move;
    }
    return move;
}

int random(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(
        0, moves.size() - 1);

    if (moves.empty()) {
        return -1;
    }
    return moves.at(dist(rng));
}

int miniMax(Player player, const Rules& rules, const Board& state) {
    const int depth = 7;
    const int alpha = N_INFINITY;
    const int beta = P_INFINITY;

    // Transposition table
    Table table;

    return _alphaBeta(player, rules, state, depth, alpha, beta, table).move;
}

int mtdf(Player player, const Rules& rules, const Board& state) {
    SearchResult result;
    const int depth = 9;
    // Transposition table
    Table table;

    for (int d = 1; d < depth; ++d) {
        result = _mtdf(player, rules, state, result.eval, d, table);
    }

    return result.move;
}

} // namespace MankalaEngine
