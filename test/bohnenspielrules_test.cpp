/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <bohnenspielrules.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Valid move", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 6; ++i) {
        CHECK(rules.validMove(i, p1, board));
        CHECK(rules.validMove(i, p2, board));
    }
}

TEST_CASE("Invalid move", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    std::vector<int> p1_holes(6, 0);
    board.holes.insert(board.holes.begin(), p1_holes.begin(), p1_holes.end());
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 6; ++i) {
        CHECK_FALSE(rules.validMove(i, p1, board));
        CHECK(rules.validMove(i, p2, board));
    }
}

TEST_CASE("Simple move", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard next_board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) += 1;
    next_board.holes.at(2) += 1;
    next_board.holes.at(3) += 1;
    next_board.holes.at(4) += 1;
    next_board.holes.at(5) += 1;
    next_board.holes.at(6) += 1;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        CHECK(board.holes.at(i) == next_board.holes.at(i));
    }
}

TEST_CASE("Lap move", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard next_board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    next_board.holes.at(8) = 0;
    next_board.holes.at(9) += 1;
    next_board.holes.at(10) += 1;
    next_board.holes.at(11) += 1;
    next_board.holes.at(0) += 1;
    next_board.holes.at(1) += 1;
    next_board.holes.at(2) += 1;

    rules.move(2, p2, board);
    for (int i = 0; i < 12; ++i) {
        CHECK(board.holes.at(i) == next_board.holes.at(i));
    }
}

TEST_CASE("Move with single capture", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard next_board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;

    board.holes = std::vector<int>(12, 0);
    next_board.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 1;
    board.holes.at(1) = 1;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) = 0;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        CHECK(board.holes.at(i) == next_board.holes.at(i));
    }
    CHECK(board.stores.at(0) == 2);
    CHECK(board.stores.at(1) == 0);
}

TEST_CASE("Move with multiple captures", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard next_board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;

    board.holes = std::vector<int>(12, 0);
    next_board.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 2;
    board.holes.at(1) = 1;
    board.holes.at(2) = 1;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) = 0;
    next_board.holes.at(1) = 0;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        CHECK(board.holes.at(i) == next_board.holes.at(i));
    }
    CHECK(board.stores.at(0) == 4);
    CHECK(board.stores.at(1) == 0);
}

TEST_CASE("Capture with lap", "BohnenspielRules") {
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard next_board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    board.holes.at(8) = 5;
    board.holes.at(9) = 1;
    board.holes.at(10) = 1;
    board.holes.at(11) = 3;
    board.holes.at(0) = 5;
    board.holes.at(1) = 1;
    board.holes.at(2) = 0;

    next_board.holes.at(8) = 0;
    next_board.holes.at(9) = 0;
    next_board.holes.at(10) = 0;
    next_board.holes.at(11) = 0;
    next_board.holes.at(0) = 0;
    next_board.holes.at(1) = 0;
    next_board.holes.at(2) = 0;

    rules.move(2, p2, board);
    for (int i = 0; i < 12; ++i) {
        CHECK(board.holes.at(i) == next_board.holes.at(i));
    }
    CHECK(board.stores.at(0) == 0);
    CHECK(board.stores.at(1) == 16);
}
