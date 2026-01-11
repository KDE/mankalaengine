/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "moveselection.h"

#include "rules.h"

// C++
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

namespace MankalaEngine {

bool _greater(int x, int y) { return x > y; }

bool _less(int x, int y) { return x < y; }

// This function was adapted from the following Stack Overflow answer:
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector/72073933#72073933
unsigned int _hash(Player player, const Board& state) {
    unsigned int hash = player;
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

// Allow a cognitive complexity greater than 25, since that's how the referenced
// pseudo-code describes the algorithm
// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SearchResult _alphaBeta(Player player, const Rules& rules, const Board& state,
                        int depth, int alpha, int beta, Table& table) {

    SearchResult result;
    const unsigned int hash = _hash(player, state);
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

    if (depth == 0 || rules.isGameOver(player, state)) { // Leaf node
        result.eval = _eval(state);
    } else if (player == player_1) { // Max node
        int a = alpha;
        result.eval = N_INFINITY;

        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            Board new_state = state;
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
        }
    } else { // Min node
        int b = beta;
        result.eval = P_INFINITY;

        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            Board new_state = state;
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
    int upperbound = P_INFINITY;
    int lowerbound = N_INFINITY;
    SearchResult guess;

    guess.eval = first_guess;

    // Allow using do-while, since that's how the original pseudo-code describes
    // the algorithm
    do { // NOLINT(cppcoreguidelines-avoid-do-while)
        const int beta = guess.eval == lowerbound ? guess.eval + 1 : guess.eval;
        guess = _alphaBeta(player, rules, state, depth, beta - 1, beta, table);
        if (guess.eval < beta) {
            upperbound = guess.eval;
        } else {
            lowerbound = guess.eval;
        }
    } while (lowerbound < upperbound);
    return guess;
}

int user(Player player, const Rules& rules, const Board& state) {
    int move = -1;
    std::cin >> move;
    while (!rules.isValidMove(move, player, state)) {
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

int greedy(Player player, const Rules& rules, const Board& state) {
    int bestValue = N_INFINITY;
    int bestMove = -1;
    const auto moves = rules.getMoves(player, state);

    for (const auto& move : moves) {
        Board new_state = state;
        rules.move(move, player, new_state);
        if (_eval(new_state) > bestValue) {
            bestValue = _eval(new_state);
            bestMove = move;
        }
    }

    return bestMove;
}

} // namespace MankalaEngine
