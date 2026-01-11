/*
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "kalahrules.h"
#include "rules.h"

// Qt
#include <QTest>

// C++
#include <iostream>
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
    int played_move = 0;
    MankalaEngine::Player player = MankalaEngine::player_1;
    MankalaEngine::KalahBoard board;
    MankalaEngine::KalahBoard result;

    result.holes.at(0) = 0;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;
    result.holes.at(5) += 1;
    result.stores.at(player) += 1;

    QTest::newRow("simple-move") << played_move << player << board << result;

    // Testing a move with a lap
    played_move = 0;
    player = MankalaEngine::player_1;
    board = MankalaEngine::KalahBoard();
    result = MankalaEngine::KalahBoard();

    result.holes = std::vector<int>(12, 7);

    board.holes.at(0) = 13;

    result.holes.at(0) = 0;
    result.holes.at(1) = 8;
    result.stores.at(0) = 1;

    QTest::newRow("lap-move") << played_move << player << board << result;

    // Testing a move with a single capture
    played_move = 3;
    player = MankalaEngine::player_1;
    board = MankalaEngine::KalahBoard();
    result = MankalaEngine::KalahBoard();

    board.holes.at(3) = 2;
    board.holes.at(4) = 1;
    board.holes.at(5) = 0;
    board.holes.at(6) = 2;

    result.holes.at(3) = 0;
    result.holes.at(4) = 2;
    result.holes.at(5) = 0;
    result.holes.at(6) = 0;

    result.stores.at(0) = 3;
    result.stores.at(1) = 0;

    QTest::newRow("capture-move") << played_move << player << board << result;

    // Testing a move with a capture with passing over kalahs
    played_move = 4;
    player = MankalaEngine::player_1;
    board = MankalaEngine::KalahBoard();
    result = MankalaEngine::KalahBoard();

    board.holes.at(1) = 0;
    board.holes.at(4) = 10;

    result.holes.at(4) = 0;
    result.holes.at(5) = 7;
    result.holes.at(6) = 7;
    result.holes.at(7) = 7;
    result.holes.at(8) = 7;
    result.holes.at(9) = 7;
    result.holes.at(10) = 0;
    result.holes.at(11) = 7;
    result.holes.at(0) = 7;
    result.holes.at(1) = 0;

    result.stores.at(player) = 9;

    QTest::newRow("capture-with-passing-over-kalahs-move")
        << played_move << player << board << result;
}

void TestKalahRules::move() {
    QFETCH(int, played_move);
    QFETCH(MankalaEngine::Player, player);
    QFETCH(MankalaEngine::KalahBoard, board);
    QFETCH(MankalaEngine::KalahBoard, result);
    MankalaEngine::KalahRules rules;

    rules.move(played_move, player, board);

    for (int i = 0; i < 12; ++i) {
        std::cout << "i " << i << " b(i) " << board.holes.at(i) << " r(i) "
                  << result.holes.at(i) << "\n";
        QCOMPARE(board.holes.at(i), result.holes.at(i));
    }
    QCOMPARE(board.stores.at(MankalaEngine::player_1),
             result.stores.at(MankalaEngine::player_1));
    QCOMPARE(board.stores.at(MankalaEngine::player_2),
             result.stores.at(MankalaEngine::player_2));
}

void TestKalahRules::isValidMove_data() {
    QTest::addColumn<MankalaEngine::KalahBoard>("board");
    QTest::addColumn<bool>("p1_result");
    QTest::addColumn<bool>("p2_result");

    // Testing with a board where every move is valid
    MankalaEngine::KalahBoard board;

    QTest::newRow("valid-move") << board << true << true;

    // Testing with a board where every player 1 move is invalid, player 1 has
    // no pebbles.
    std::vector<int> p1_holes(6, 0);
    board.holes.insert(board.holes.begin(), p1_holes.begin(), p1_holes.end());

    QTest::newRow("invalid-move") << board << false << true;
}

void TestKalahRules::isValidMove() {
    QFETCH(MankalaEngine::KalahBoard, board);
    QFETCH(bool, p1_result);
    QFETCH(bool, p2_result);
    MankalaEngine::KalahRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 6; ++i) {
        QCOMPARE(rules.isValidMove(i, p1, board), p1_result);
        QCOMPARE(rules.isValidMove(i, p2, board), p2_result);
    }
}

QTEST_MAIN(TestKalahRules)
#include "TestKalahRules.moc"
