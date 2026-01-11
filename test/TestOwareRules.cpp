/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "owarerules.h"
#include "rules.h"

// Qt
#include <QTest>

// C++
#include <utility>
#include <vector>

class TestOwareRules : public QObject {
    Q_OBJECT
  private Q_SLOTS:
    void move_data();
    void move();
    void isValidMove_data();
    void isValidMove();
};

void TestOwareRules::move_data() {
    QTest::addColumn<int>("played_move");
    QTest::addColumn<MankalaEngine::Player>("player");
    QTest::addColumn<MankalaEngine::OwareBoard>("board");
    QTest::addColumn<MankalaEngine::OwareBoard>("result");

    // Testing a simple move
    int played_move = 0;
    MankalaEngine::Player player = MankalaEngine::player_1;
    MankalaEngine::OwareBoard board;
    MankalaEngine::OwareBoard result;

    result.holes.at(0) = 0;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;

    QTest::newRow("simple-move") << played_move << player << board << result;

    // Testing a move with a lap
    played_move = 0;
    player = MankalaEngine::player_1;
    board = MankalaEngine::OwareBoard();
    result = MankalaEngine::OwareBoard();

    result.holes = std::vector<int>(12, 5);

    board.holes.at(0) = 12;

    result.holes.at(0) = 0;
    result.holes.at(1) = 6;

    QTest::newRow("lap-move") << played_move << player << board << result;

    // Testing a move with a single capture
    played_move = 5;
    player = MankalaEngine::player_1;
    board = MankalaEngine::OwareBoard();
    result = MankalaEngine::OwareBoard();

    board.holes.at(5) = 1;
    board.holes.at(6) = 1;

    result.holes.at(5) = 0;
    result.holes.at(6) = 0;

    result.stores.at(0) = 2;
    result.stores.at(1) = 0;

    QTest::newRow("single-capture-move")
        << played_move << player << board << result;

    // Testing a move with mutiple captures
    played_move = 5;
    player = MankalaEngine::player_1;
    board = MankalaEngine::OwareBoard();
    result = MankalaEngine::OwareBoard();

    board.holes.at(5) = 2;
    board.holes.at(6) = 1;
    board.holes.at(7) = 1;

    result.holes.at(5) = 0;
    result.holes.at(6) = 0;
    result.holes.at(7) = 0;

    result.stores.at(0) = 4;
    result.stores.at(1) = 0;

    QTest::newRow("multiple-captures-move")
        << played_move << player << board << result;

    // Testing a Grand Slam
    played_move = 5;
    player = MankalaEngine::player_1;
    board = MankalaEngine::OwareBoard();
    result = MankalaEngine::OwareBoard();

    board.holes = std::vector(12, 2);
    result.holes = std::vector(12, 2);

    board.holes.at(5) = 6;
    result.holes.at(5) = 0;

    std::vector<int> p2_holes(6, 3);
    result.holes.insert(result.holes.begin() + 6, p2_holes.begin(),
                        p2_holes.end());

    QTest::newRow("grand-slam") << played_move << player << board << result;
}

void TestOwareRules::move() {
    QFETCH(int, played_move);
    QFETCH(MankalaEngine::Player, player);
    QFETCH(MankalaEngine::OwareBoard, board);
    QFETCH(MankalaEngine::OwareBoard, result);
    MankalaEngine::OwareRules rules;

    rules.move(played_move, player, board);

    for (int i = 0; i < 12; ++i) {
        QCOMPARE(board.holes.at(i), result.holes.at(i));
    }
    QCOMPARE(board.stores.at(0), result.stores.at(0));
    QCOMPARE(board.stores.at(1), result.stores.at(1));
}

void TestOwareRules::isValidMove_data() {
    QTest::addColumn<MankalaEngine::OwareBoard>("board");
    QTest::addColumn<bool>("p1_result");
    QTest::addColumn<bool>("p2_result");

    // Testing with a board where every move is valid
    MankalaEngine::OwareBoard board;

    QTest::newRow("valid-move") << board << true << true;

    // Testing with a board where every move is invalid, since player 1 has no
    // pebbles and player 2 has no move that can change this.
    board.holes = std::vector(12, 0);
    board.holes.at(6) = 4;
    board.holes.at(7) = 4;

    QTest::newRow("invalid-move") << board << false << false;
}

void TestOwareRules::isValidMove() {
    QFETCH(MankalaEngine::OwareBoard, board);
    QFETCH(bool, p1_result);
    QFETCH(bool, p2_result);
    MankalaEngine::OwareRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 6; ++i) {
        QCOMPARE(rules.isValidMove(i, p1, board), p1_result);
        QCOMPARE(rules.isValidMove(i, p2, board), p2_result);
    }
}

QTEST_MAIN(TestOwareRules)
#include "TestOwareRules.moc"
