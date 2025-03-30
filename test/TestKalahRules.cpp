/*
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QTest>
#include <kalahrules.h>
#include <rules.h>
#include <utility>
#include <vector>

class TestKalahRules : public QObject {
    Q_OBJECT
  private Q_SLOTS:
    void move_data();
    void move();
    void isValidMove_data();
    void isValidMove();
};

void TestKalahRules::move_data() {
    QTest::addColumn<int>("played_move");
    QTest::addColumn<MankalaEngine::Player>("player");
    QTest::addColumn<MankalaEngine::KalahBoard>("board");
    QTest::addColumn<MankalaEngine::KalahBoard>("result");

    // Testing a simple move
    int played_move = 1;
    MankalaEngine::Player player = MankalaEngine::player_1;
    MankalaEngine::KalahBoard board;
    MankalaEngine::KalahBoard result;

    result.holes.at(1) = 0;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;
    result.holes.at(5) += 1;
    result.holes.at(6) += 1;
    result.stores.at(player) += 1;

    QTest::newRow("simple-move") << played_move << player << board << result;

    // Testing a move with a lap
    played_move = 1;
    player = MankalaEngine::player_1;
    board = MankalaEngine::KalahBoard();
    result = MankalaEngine::KalahBoard();

    result.holes = std::vector<int>(14, 5);

    board.holes.at(1) = 12;

    result.holes.at(1) = 0;
    result.holes.at(2) = 6;

    QTest::newRow("lap-move") << played_move << player << board << result;

    // Testing a move with a single capture
    played_move = 3;
    player = MankalaEngine::player_1;
    board = MankalaEngine::KalahBoard();
    result = MankalaEngine::KalahBoard();

    board.holes.at(3) = 2;
    board.holes.at(4) = 1;
    board.holes.at(5) = 0;
    board.holes.at(8) = 2;

    result.holes.at(3) = 0;
    result.holes.at(4) = 2;
    result.holes.at(5) = 0;
    result.holes.at(8) = 0;

    result.stores.at(0) = 3;
    result.stores.at(1) = 0;

    QTest::newRow("capture-move")
        << played_move << player << board << result;
}

void TestKalahRules::move() {
    QFETCH(int, played_move);
    QFETCH(MankalaEngine::Player, player);
    QFETCH(MankalaEngine::KalahBoard, board);
    QFETCH(MankalaEngine::KalahBoard, result);
    MankalaEngine::KalahRules rules;

    rules.move(played_move, player, board);

    for (int i = 1; i <= 14; ++i) {
        QCOMPARE(board.holes.at(i%14), result.holes.at(i%14));
    }
    QCOMPARE(board.stores.at(MankalaEngine::player_1), result.stores.at(MankalaEngine::player_1));
    QCOMPARE(board.stores.at(MankalaEngine::player_2), result.stores.at(MankalaEngine::player_2));
}

void TestKalahRules::isValidMove_data() {
    QTest::addColumn<MankalaEngine::KalahBoard>("board");
    QTest::addColumn<bool>("p1_result");
    QTest::addColumn<bool>("p2_result");

    // Testing with a board where every move is valid
    MankalaEngine::KalahBoard board;

    QTest::newRow("valid-move") << board << true << true;

    // Testing with a board where every move is invalid, since player 1 has no
    // pebbles and player 2 has no move that can change this.
    board.holes = std::vector(14, 0);
    board.holes.at(8) = 4;
    board.holes.at(9) = 4;

    QTest::newRow("invalid-move") << board << false << false;
}

void TestKalahRules::isValidMove() {
    QFETCH(MankalaEngine::KalahBoard, board);
    QFETCH(bool, p1_result);
    QFETCH(bool, p2_result);
    MankalaEngine::KalahRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 1; i < 7; ++i) {
        QCOMPARE(rules.isValidMove(i, p1, board), p1_result);
        QCOMPARE(rules.isValidMove(i, p2, board), p2_result);
    }
}

QTEST_MAIN(TestKalahRules)
#include "TestKalahRules.moc"
