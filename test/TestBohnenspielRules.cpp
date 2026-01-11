/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "bohnenspielrules.h"
#include "rules.h"

// Qt
#include <QTest>

// C++
#include <utility>
#include <vector>

class TestBohnenspielRules : public QObject {
    Q_OBJECT
  private Q_SLOTS:
    void move_data();
    void move();
    void isValidMove_data();
    void isValidMove();
};

void TestBohnenspielRules::move_data() {
    QTest::addColumn<int>("played_move");
    QTest::addColumn<MankalaEngine::Player>("player");
    QTest::addColumn<MankalaEngine::BohnenspielBoard>("board");
    QTest::addColumn<MankalaEngine::BohnenspielBoard>("result");

    // Testing a simple move
    int played_move = 0;
    MankalaEngine::Player player = MankalaEngine::player_1;
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielBoard result;

    result.holes.at(0) = 0;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;
    result.holes.at(5) += 1;
    result.holes.at(6) += 1;

    QTest::newRow("simple-move") << played_move << player << board << result;

    // Testing a lap move
    played_move = 2;
    player = MankalaEngine::player_2;
    result = MankalaEngine::BohnenspielBoard();

    result.holes.at(8) = 0;
    result.holes.at(9) += 1;
    result.holes.at(10) += 1;
    result.holes.at(11) += 1;
    result.holes.at(0) += 1;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;

    QTest::newRow("lap-move") << played_move << player << board << result;

    // Testing a move with a single capture
    played_move = 0;
    player = MankalaEngine::player_1;

    board.holes = std::vector<int>(12, 0);
    result.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 1;
    board.holes.at(1) = 1;

    result.stores.at(0) = 2;
    result.stores.at(1) = 0;

    QTest::newRow("single-capture-move")
        << played_move << player << board << result;

    // Testing a move with mutiple captures
    played_move = 0;
    player = MankalaEngine::player_1;

    board.holes = std::vector<int>(12, 0);
    result.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 2;
    board.holes.at(1) = 1;
    board.holes.at(2) = 1;

    result.stores.at(0) = 4;
    result.stores.at(1) = 0;

    QTest::newRow("multiple-captures-move")
        << played_move << player << board << result;

    // Testing a move with a capture with a lap
    played_move = 2;
    player = MankalaEngine::player_2;
    board = MankalaEngine::BohnenspielBoard();
    result = MankalaEngine::BohnenspielBoard();

    board.holes.at(8) = 5;
    board.holes.at(9) = 1;
    board.holes.at(10) = 1;
    board.holes.at(11) = 3;
    board.holes.at(0) = 5;
    board.holes.at(1) = 1;
    board.holes.at(2) = 0;

    result.holes.at(8) = 0;
    result.holes.at(9) = 0;
    result.holes.at(10) = 0;
    result.holes.at(11) = 0;
    result.holes.at(0) = 0;
    result.holes.at(1) = 0;
    result.holes.at(2) = 0;

    result.stores.at(0) = 0;
    result.stores.at(1) = 16;

    QTest::newRow("capture-with-lap-move")
        << played_move << player << board << result;
}

void TestBohnenspielRules::move() {
    QFETCH(int, played_move);
    QFETCH(MankalaEngine::Player, player);
    QFETCH(MankalaEngine::BohnenspielBoard, board);
    QFETCH(MankalaEngine::BohnenspielBoard, result);
    MankalaEngine::BohnenspielRules rules;

    rules.move(played_move, player, board);

    for (int i = 0; i < 12; ++i) {
        QCOMPARE(board.holes.at(i), result.holes.at(i));
    }
    QCOMPARE(board.stores.at(0), result.stores.at(0));
    QCOMPARE(board.stores.at(1), result.stores.at(1));
}

void TestBohnenspielRules::isValidMove_data() {
    QTest::addColumn<MankalaEngine::BohnenspielBoard>("board");
    QTest::addColumn<bool>("p1_result");
    QTest::addColumn<bool>("p2_result");

    // Testing with a board where every move is valid
    MankalaEngine::BohnenspielBoard board;

    QTest::newRow("valid-move") << board << true << true;

    // Testing with a board where every player 1 move is invalid
    std::vector<int> p1_holes(6, 0);
    board.holes.insert(board.holes.begin(), p1_holes.begin(), p1_holes.end());

    QTest::newRow("invalid-move") << board << false << true;
}

void TestBohnenspielRules::isValidMove() {
    QFETCH(MankalaEngine::BohnenspielBoard, board);
    QFETCH(bool, p1_result);
    QFETCH(bool, p2_result);
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 6; ++i) {
        QCOMPARE(rules.isValidMove(i, p1, board), p1_result);
        QCOMPARE(rules.isValidMove(i, p2, board), p2_result);
    }
}

QTEST_MAIN(TestBohnenspielRules)
#include "TestBohnenspielRules.moc"
