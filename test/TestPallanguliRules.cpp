/*
    SPDX-FileCopyrightText: 2025 Shubham Shinde <shubshinde8381@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "pallangulirules.h"
#include "rules.h"

// Qt
#include <QTest>

// C++
#include <utility>
#include <vector>

class TestPallanguliRules : public QObject {
    Q_OBJECT
  private Q_SLOTS:
    void move_data();
    void move();
    void isValidMove_data();
    void isValidMove();
};

void TestPallanguliRules::move_data() {
    QTest::addColumn<int>("played_move");
    QTest::addColumn<MankalaEngine::Player>("player");
    QTest::addColumn<MankalaEngine::PallanguliBoard>("board");
    QTest::addColumn<MankalaEngine::PallanguliBoard>("result");

    // Testing a simple single move
    int played_move = 0;
    MankalaEngine::Player player = MankalaEngine::player_1;
    MankalaEngine::PallanguliBoard board;
    MankalaEngine::PallanguliBoard result;

    board.holes = std::vector<int>(14, 0);
    result.holes = std::vector<int>(14, 0);

    board.holes.at(0) = 6;

    result.holes.at(0) = 0;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;
    result.holes.at(5) += 1;
    result.holes.at(6) += 1;

    QTest::newRow("simple-single-move")
        << played_move << player << board << result;

    // Testing single lap move
    played_move = 5;
    player = MankalaEngine::player_2;
    result = MankalaEngine::PallanguliBoard();

    board.holes = std::vector<int>(14, 0);
    result.holes = std::vector<int>(14, 0);

    board.holes.at(12) = 6;
    result.holes.at(12) = 0;
    result.holes.at(13) += 1;
    result.holes.at(0) += 1;
    result.holes.at(1) += 1;
    result.holes.at(2) += 1;
    result.holes.at(3) += 1;
    result.holes.at(4) += 1;

    QTest::newRow("single-lap-move")
        << played_move << player << board << result;

    // Testing a move with a single capture
    played_move = 0;
    player = MankalaEngine::player_1;

    board.holes = std::vector<int>(14, 0);
    result.holes = std::vector<int>(14, 0);

    board.holes.at(0) = 3;
    board.holes.at(1) = 0;
    board.holes.at(5) = 5;

    result.holes.at(0) = 0;
    result.holes.at(1) = 1;
    result.holes.at(2) = 1;
    result.holes.at(3) = 1;
    result.holes.at(5) = 0;
    result.stores.at(0) = 5;

    QTest::newRow("single-capture-move")
        << played_move << player << board << result;

    // Testing a move with a capture with a lap
    played_move = 3;
    player = MankalaEngine::player_2;
    board.holes = std::vector<int>(14, 0);
    result.holes = std::vector<int>(14, 0);

    board.holes.at(10) = 3;
    board.holes.at(11) = 0;
    board.holes.at(1) = 5;

    result.holes.at(10) = 0;
    result.holes.at(11) = 1;
    result.holes.at(12) = 1;
    result.holes.at(13) = 1;
    result.holes.at(1) = 0;

    result.stores.at(0) = 0;
    result.stores.at(1) = 5;

    QTest::newRow("capture-with-lap-move")
        << played_move << player << board << result;

    // Testing capture after empty pit
    played_move = 5;
    player = MankalaEngine::player_2;

    board.holes = std::vector<int>(14, 0);
    result.holes = std::vector<int>(14, 0);

    board.holes.at(12) = 7;
    board.holes.at(7) = 5;

    result.holes.at(12) = 0;
    result.holes.at(13) = 1;
    result.holes.at(0) = 1;
    result.holes.at(1) = 1;
    result.holes.at(2) = 1;
    result.holes.at(3) = 1;
    result.holes.at(4) = 1;
    result.holes.at(5) = 1;
    // pit6 is empty.
    result.holes.at(7) = 0;

    result.stores.at(0) = 0;
    result.stores.at(1) = 5;

    QTest::newRow("capture-after-empty")
        << played_move << player << board << result;
}

void TestPallanguliRules::move() {
    QFETCH(int, played_move);
    QFETCH(MankalaEngine::Player, player);
    QFETCH(MankalaEngine::PallanguliBoard, board);
    QFETCH(MankalaEngine::PallanguliBoard, result);
    MankalaEngine::PallanguliRules rules;

    rules.move(played_move, player, board);

    for (int i = 0; i < 14; ++i) {
        QCOMPARE(board.holes.at(i), result.holes.at(i));
    }
    QCOMPARE(board.stores.at(0), result.stores.at(0));
    QCOMPARE(board.stores.at(1), result.stores.at(1));
}

void TestPallanguliRules::isValidMove_data() {
    QTest::addColumn<MankalaEngine::PallanguliBoard>("board");
    QTest::addColumn<bool>("p1_result");
    QTest::addColumn<bool>("p2_result");

    // Testing with a board where every move is valid
    MankalaEngine::PallanguliBoard board;

    QTest::newRow("valid-move") << board << true << true;

    // Testing with a board where every player 1 move is invalid
    std::vector<int> p1_holes(7, 0);
    board.holes.insert(board.holes.begin(), p1_holes.begin(), p1_holes.end());

    QTest::newRow("invalid-move") << board << false << true;
}

void TestPallanguliRules::isValidMove() {
    QFETCH(MankalaEngine::PallanguliBoard, board);
    QFETCH(bool, p1_result);
    QFETCH(bool, p2_result);
    MankalaEngine::PallanguliRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    for (int i = 0; i < 7; ++i) {
        QCOMPARE(rules.isValidMove(i, p1, board), p1_result);
        QCOMPARE(rules.isValidMove(i, p2, board), p2_result);
    }
}

QTEST_MAIN(TestPallanguliRules)
#include "TestPallanguliRules.moc"
