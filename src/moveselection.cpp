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

struct NodeScore {
    int lowerbound = N_INFINITY;
    int upperbound = P_INFINITY;
};

typedef std::unordered_map<int, std::unique_ptr<NodeScore>> Table;

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

int _alphaBeta(Player player, const Rules& rules, const Board& state, int depth,
               int alpha, int beta, Table& table) {

    int eval = 0;
    const int hash = _hash(player, state);
    auto emplace_result = table.emplace(hash, std::make_unique<NodeScore>());
    const auto entry = emplace_result.first;

    if (!emplace_result.second) { // Emplace failed, entry already exists
        if (entry->second->lowerbound >= beta) {
            return entry->second->lowerbound;
        }
        if (entry->second->upperbound <= alpha) {
            return entry->second->upperbound;
        }

        alpha = std::max(alpha, entry->second->lowerbound);
        beta = std::min(beta, entry->second->upperbound);
    }

    if (depth == 0 || rules.gameOver(player, state)) { // Leaf node
        eval = _eval(state);
    } else if (player == player_1) { // Max node
        int a = alpha;
        eval = N_INFINITY;

        Board new_state = state;
        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            eval = std::max(eval, _alphaBeta(player_2, rules, new_state,
                                             depth - 1, a, beta, table));

            if (eval >= beta) {
                break;
            }

            a = std::max(a, eval);
            new_state = state; // Undo previous move
        }
    } else { // Min node
        int b = beta;
        eval = P_INFINITY;

        Board new_state = state;
        const auto moves = rules.getMoves(player, state);

        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            eval = std::min(eval, _alphaBeta(player_2, rules, new_state,
                                             depth - 1, alpha, b, table));

            if (eval <= alpha) {
                break;
            }

            b = std::min(b, eval);
            new_state = state; // Undo previous move
        }
    }

    if (eval <= alpha) {
        entry->second->lowerbound = eval;
    }
    if (eval >= beta) {
        entry->second->upperbound = eval;
    }
    if (eval > alpha && eval < beta) {
        entry->second->lowerbound = eval;
        entry->second->upperbound = eval;
    }
    return eval;
}

int _mtdf(Player player, const Rules& rules, const Board& state,
          int first_guess, int depth, Table& table) {
    int beta, g = first_guess;
    int upperbound = P_INFINITY;
    int lowerbound = N_INFINITY;

    do {
        beta = g == lowerbound ? g + 1 : g;
        g = _alphaBeta(player, rules, state, depth, beta - 1, beta, table);
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    } while (lowerbound < upperbound);
    return g;
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
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }
    int chosen_move = -1;

    int best_eval = player == player_1 ? N_INFINITY : P_INFINITY;
    const auto is_better = player == player_1 ? _greater : _less;
    const int depth = 7;
    const int alpha = N_INFINITY;
    const int beta = P_INFINITY;

    // Transposition table
    Table table;

    Board new_state = state;
    for (const auto& move : moves) {
        rules.move(move, player, new_state);
        const int eval =
            _alphaBeta(player, rules, new_state, depth, alpha, beta, table);

        if (is_better(eval, best_eval)) {
            best_eval = eval;
            chosen_move = move;
        }
        new_state = state; // Undo previous move
    }

    return chosen_move;
}

int mtdf(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }

    int chosen_move = -1;
    int eval = 0;
    int best_eval = player == player_1 ? N_INFINITY : P_INFINITY;
    const auto is_better = player == player_1 ? _greater : _less;
    const int depth = 9;

    // Transposition table
    Table table;

    Board new_state = state;
    for (const auto& move : moves) {
        rules.move(move, player, new_state);
        for (int d = 1; d < depth; ++d) {
            eval = _mtdf(player, rules, new_state, eval, d, table);
            if (is_better(eval, best_eval)) {
                best_eval = eval;
                chosen_move = move;
            }
        }
        new_state = state; // Undo previous move
    }

    return chosen_move;
}

} // namespace MankalaEngine
