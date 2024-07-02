/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <moveselection.h>
#include <unordered_map>

namespace MankalaEngine {

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
               int alpha, int beta, std::unordered_map<int, int>& table) {

    const int hash = _hash(player, state);
    const auto entry = table.find(hash);
    if (entry != table.end()) {
        return entry->second;
    }

    if (depth == 0 || rules.gameOver(player, state)) {
        return _eval(state);
    }

    const auto moves = rules.getMoves(player, state);
    Board new_state = state;

    if (player == player_1) {
        int highest_eval = std::numeric_limits<int>::min(); // Negative infinity
        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            const int eval = _alphaBeta(player_2, rules, new_state, depth - 1,
                                        alpha, beta, table);
            highest_eval = std::max(highest_eval, eval);
            if (highest_eval > beta) {
                break;
            }
            alpha = std::max(highest_eval, alpha);
            new_state = state; // Undo previous move
        }

        table.emplace(hash, highest_eval);
        return highest_eval;
    }

    int lowest_eval = std::numeric_limits<int>::max(); // Positive infinity
    for (const auto& move : moves) {
        rules.move(move, player, new_state);
        const int eval = _alphaBeta(player_1, rules, new_state, depth - 1,
                                    alpha, beta, table);
        lowest_eval = std::min(lowest_eval, eval);
        if (lowest_eval < alpha) {
            break;
        }
        alpha = std::min(lowest_eval, alpha);
        new_state = state; // Undo previous move
    }

    table.emplace(hash, lowest_eval);
    return lowest_eval;
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
    if (moves.empty()) {
        return -1;
    }
    std::srand(std::time(0));
    return moves.at(std::rand() % moves.size());
}

int miniMax(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }
    int chosen_move = -1;

    const int depth = 6;
    // Negative infinity
    const int alpha = std::numeric_limits<int>::min();
    // Positive infinity
    const int beta = std::numeric_limits<int>::max();
    // Transposition table
    std::unordered_map<int, int> table;

    if (player == player_1) {
        int highest_eval = std::numeric_limits<int>::min(); // Negative infinity
        for (const auto& move : moves) {
            const int eval =
                _alphaBeta(player, rules, state, depth, alpha, beta, table);
            if (eval > highest_eval) {
                highest_eval = eval;
                chosen_move = move;
            }
        }
    } else {
        int lowest_eval = std::numeric_limits<int>::max(); // Positive infinity
        for (const auto& move : moves) {
            const int eval =
                _alphaBeta(player, rules, state, depth, alpha, beta, table);
            if (eval < lowest_eval) {
                lowest_eval = eval;
                chosen_move = move;
            }
        }
    }

    return chosen_move;
}

} // namespace MankalaEngine
