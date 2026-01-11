/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "bohnenspielrules.h"
#include "mankalaengine.h"
#include "moveselection.h"

// Qt
#include <QTest>

class TestMankalaEngine : public QObject {
    Q_OBJECT
  private Q_SLOTS:
    void play_data();
    void play();
};

void TestMankalaEngine::play_data() {
    QTest::addColumn<MankalaEngine::MankalaEngine>("engine");

    MankalaEngine::MankalaEngine random(MankalaEngine::random);
    QTest::newRow("random-selection") << random;

    MankalaEngine::MankalaEngine miniMax(MankalaEngine::miniMax);
    QTest::newRow("miniMax-selection") << miniMax;

    MankalaEngine::MankalaEngine mtdf(MankalaEngine::mtdf);
    QTest::newRow("mtdf-selection") << mtdf;
}

void TestMankalaEngine::play() {
    QFETCH(MankalaEngine::MankalaEngine, engine);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    while (engine.play(p1, rules, board) && engine.play(p2, rules, board)) {
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        QVERIFY(!rules.isValidMove(i, p1, board));
        QVERIFY(!rules.isValidMove(i, p2, board));
    }
    QCOMPARE(board.stores.at(p1) + board.stores.at(p2), 6 * 6 * 2);
}

QTEST_MAIN(TestMankalaEngine)
#include "TestMankalaEngine.moc"
