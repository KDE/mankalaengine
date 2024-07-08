/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <bohnenspielrules.h>
#include <catch2/catch_test_macros.hpp>
#include <mankalaengine.h>
#include <moveselection.h>

TEST_CASE("Random selection full Bohnenspiel game", "MankalaEngine") {
    MankalaEngine::MankalaEngine engine(MankalaEngine::random);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    while (engine.play(p1, rules, board) && engine.play(p2, rules, board)) {
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        CHECK_FALSE(rules.validMove(i, p1, board));
        CHECK_FALSE(rules.validMove(i, p2, board));
    }
    CHECK(board.stores.at(p1) + board.stores.at(p2) == 6 * 6 * 2);
}

TEST_CASE("Minimax selection full Bohnenspiel game", "MankalaEngine") {
    MankalaEngine::MankalaEngine engine(MankalaEngine::miniMax);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    while (engine.play(p1, rules, board) && engine.play(p2, rules, board)) {
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        CHECK_FALSE(rules.validMove(i, p1, board));
        CHECK_FALSE(rules.validMove(i, p2, board));
    }
    CHECK(board.stores.at(p1) + board.stores.at(p2) == 6 * 6 * 2);
}

TEST_CASE("MTDF selection full Bohnenspiel game", "MankalaEngine") {
    MankalaEngine::MankalaEngine engine(MankalaEngine::mtdf);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    while (engine.play(p1, rules, board) && engine.play(p2, rules, board)) {
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        CHECK_FALSE(rules.validMove(i, p1, board));
        CHECK_FALSE(rules.validMove(i, p2, board));
    }
    CHECK(board.stores.at(p1) + board.stores.at(p2) == 6 * 6 * 2);
}
