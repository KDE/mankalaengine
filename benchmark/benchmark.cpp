/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <bohnenspielrules.h>
#include <ctime>
#include <functional>
#include <iostream>
#include <mankalaengine.h>
#include <moveselection.h>

template <class T> T create() { return T(); }

constexpr int engine_count = 2;
constexpr int rules_count = 1;

const MankalaEngine::BohnenspielRules bohnenspiel_rules;

const std::array<const MankalaEngine::MankalaEngine, engine_count> engines = {
    MankalaEngine::MankalaEngine(MankalaEngine::random),
    MankalaEngine::MankalaEngine(MankalaEngine::miniMax),
};

const std::array<const MankalaEngine::Rules*, rules_count> rules = {
    &bohnenspiel_rules,
};

const std::array<std::function<MankalaEngine::Board()>, rules_count> boards = {
    create<MankalaEngine::BohnenspielBoard>,
};

void list_engines() {
    std::cout << "\nMove selection:\n";
    std::cout << "0 - Random opponent\n";
    std::cout << "1 - Minimax opponent\n";
}

void list_rules() {
    std::cout << "\nRules:\n";
    std::cout << "0 - Bohnenspiel\n";
}

int run_games(int games, const int engine1_id, const int engine2_id,
              const int rules_id) {

    int p1_wins = 0;
    const MankalaEngine::Player p1 = MankalaEngine::player_1;
    const MankalaEngine::Player p2 = MankalaEngine::player_2;

    std::cout << "\nRunning games.\n";
    for (int game = 0; game < games; ++game) {
        MankalaEngine::Board board = boards.at(rules_id)();

        while (engines.at(engine1_id).play(p1, *rules.at(rules_id), board) &&
               engines.at(engine2_id).play(p2, *rules.at(rules_id), board)) {
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
    std::srand(std::time(0));

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

    int p1_wins = run_games(games, engine1_id, engine2_id, rules_id);
    std::cout << "\nPlayer 1 won " << p1_wins << " out of " << games
              << " games.\n";
}
