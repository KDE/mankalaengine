/*
    SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mankalaengine.h"
#include "moveselection.h"
#include "pallangulirules.h"
#include "rules.h"

// C++
#include <iostream>

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

int main() {
    MankalaEngine::MankalaEngine user(MankalaEngine::user);
    MankalaEngine::MankalaEngine opponent(MankalaEngine::miniMax);
    MankalaEngine::PallanguliBoard board;
    MankalaEngine::PallanguliRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    print_board(board);
    while (user.play(p1, rules, board) && opponent.play(p2, rules, board)) {
        std::cout << "\n";
        print_board(board);
    }

    std::cout << "\nGame finished.\n";
    if (board.stores.at(p1) > board.stores.at(p2)) {
        std::cout << "Player 1 wins.\n";
    } else if (board.stores.at(p2) > board.stores.at(p1)) {
        std::cout << "Player 2 wins.\n";
    } else {
        std::cout << "Tie.\n";
    }
}
