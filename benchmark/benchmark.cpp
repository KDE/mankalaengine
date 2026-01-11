/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "bohnenspielrules.h"
#include "kalahrules.h"
#include "mankalaengine.h"
#include "moveselection.h"
#include "owarerules.h"

// C++
#include <cctype>
#include <functional>
#include <iostream>

template <class T> T create() { return T(); }

constexpr int engine_count = 4;
constexpr int rules_count = 3;

const MankalaEngine::BohnenspielRules bohnenspiel_rules;
const MankalaEngine::OwareRules oware_rules;
const MankalaEngine::KalahRules kalah_rules;

const std::array<const MankalaEngine::MankalaEngine, engine_count> engines = {
    MankalaEngine::MankalaEngine(MankalaEngine::random),
    MankalaEngine::MankalaEngine(MankalaEngine::miniMax),
    MankalaEngine::MankalaEngine(MankalaEngine::mtdf),
    MankalaEngine::MankalaEngine(MankalaEngine::greedy),
};

const std::array<const MankalaEngine::Rules*, rules_count> rules = {
    &bohnenspiel_rules,
    &oware_rules,
    &kalah_rules,
};

const std::array<std::function<MankalaEngine::Board()>, rules_count> boards = {
    create<MankalaEngine::BohnenspielBoard>,
    create<MankalaEngine::OwareBoard>,
    create<MankalaEngine::KalahBoard>,
};

void list_engines() {
    std::cout << "\nMove selection:\n";
    std::cout << "0 - Random opponent\n";
    std::cout << "1 - Minimax opponent\n";
    std::cout << "2 - MTDF opponent\n";
    std::cout << "3 - Greedy opponent\n";
}

void list_rules() {
    std::cout << "\nRules:\n";
    std::cout << "0 - Bohnenspiel\n";
    std::cout << "1 - Oware\n";
    std::cout << "2 - Kalah\n";
}

void print_board(const MankalaEngine::Board& board) {
    size_t columns = board.holes.size() / 2;
    std::cout << "     ";
    for (size_t i = 0; i < columns; ++i) {
        std::cout << " " << columns * 2 - 1 - i << " ";
        if ((columns * 2 - 1 - i) / 10 < 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n ";
    for (size_t i = 0; i < columns + 2; ++i) {
        std::cout << "--- ";
    }
    std::cout << "\n|   |";
    for (size_t i = 0; i < columns; ++i) {
        std::cout << " " << board.holes[columns * 2 - 1 - i];
        if (board.holes[columns * 2 - 1 - i] / 10 < 1) {
            std::cout << " ";
        }
        std::cout << "|";
    }
    std::cout << "   |";
    std::cout << "\n| " << board.stores.at(MankalaEngine::player_2);
    if (board.stores.at(MankalaEngine::player_2) / 10 < 1) {
        std::cout << " ";
    }
    std::cout << "|";
    for (size_t i = 0; i < columns - 1; ++i) {
        std::cout << "--- ";
    }
    std::cout << "---";
    std::cout << "| " << board.stores.at(MankalaEngine::player_1);
    if (board.stores.at(MankalaEngine::player_1) / 10 < 1) {
        std::cout << " ";
    }
    std::cout << "|";
    std::cout << "\n|   |";
    for (size_t i = 0; i < columns; ++i) {
        std::cout << " " << board.holes[i];
        if (board.holes[i] / 10 < 1) {
            std::cout << " ";
        }
        std::cout << "|";
    }
    std::cout << "   |";
    std::cout << "\n ";
    for (size_t i = 0; i < columns + 2; ++i) {
        std::cout << "--- ";
    }
    std::cout << "\n     ";
    for (size_t i = 0; i < columns; ++i) {
        std::cout << " " << i << "  ";
    }
    std::cout << "\n";
}

int run_games(int games, const int engine1_id, const int engine2_id,
              const int rules_id, bool verbose) {

    int p1_wins = 0;
    const MankalaEngine::Player p1 = MankalaEngine::player_1;
    const MankalaEngine::Player p2 = MankalaEngine::player_2;

    std::cout << "\nRunning games.\n";
    for (int game = 0; game < games; ++game) {
        MankalaEngine::Board board = boards.at(rules_id)();

        while (engines.at(engine1_id).play(p1, *rules.at(rules_id), board) &&
               engines.at(engine2_id).play(p2, *rules.at(rules_id), board)) {
            if (verbose) {
                std::cout << "\n";
                print_board(board);
            }
        }

        std::cout << "Game " << game << ": ";
        if (board.stores.at(p1) > board.stores.at(p2)) {
            std::cout << "Player 1 won.\n";
            ++p1_wins;
        } else if (board.stores.at(p1) < board.stores.at(p2)) {
            std::cout << "Player 2 won.\n";
        } else {
            std::cout << "Tie.\n";
        }
    }

    return p1_wins;
}

int main() {
    int games = 0;
    std::cout << "How many games should be played: ";
    std::cin >> games;
    while (games < 1) {
        std::cout << "\nInvalid choice.\n";
        std::cin >> games;
    }

    list_engines();

    int engine1_id = 0;
    std::cout << "Player 1 move selection: ";
    std::cin >> engine1_id;
    while (engine1_id > engine_count || engine1_id < 0) {
        std::cout << "\nInvalid choice.\n";
        std::cin >> engine1_id;
    }

    int engine2_id = 0;
    std::cout << "Player 2 move selection: ";
    std::cin >> engine2_id;
    while (engine2_id > engine_count || engine2_id < 0) {
        std::cout << "\nInvalid choice.\n";
        std::cin >> engine2_id;
    }

    list_rules();

    int rules_id = 0;
    std::cout << "Rules to use: ";
    std::cin >> rules_id;
    while (rules_id > rules_count || rules_id < 0) {
        std::cout << "\nInvalid choice.\n";
        std::cin >> rules_id;
    }

    char verbose;
    std::cout << "\nPrint board? (y/N): ";
    std::cin >> verbose;
    verbose = std::tolower(verbose);
    while (verbose != 'y' && verbose != 'n' && verbose != '\n') {
        std::cout << "\nInvalid choice.\n";
        std::cin >> verbose;
        verbose = std::tolower(verbose);
    }

    int p1_wins =
        run_games(games, engine1_id, engine2_id, rules_id, verbose == 'y');
    std::cout << "\nPlayer 1 won " << p1_wins << " out of " << games
              << " games.\n";
}
