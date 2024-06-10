#include <bohnenspielrules.h>
#include <gtest/gtest.h>
#include <mankalaengine.h>
#include <moveselection.h>

TEST(MankalaEngine, RandomSelectionFullBohnenspielGame) {
    MankalaEngine::MankalaEngine engine(MankalaEngine::random);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::player_1;
    MankalaEngine::Player p2 = MankalaEngine::player_2;

    while (engine.play(p1, rules, board) && engine.play(p2, rules, board)) {
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        EXPECT_FALSE(rules.validMove(i, p1, board));
        EXPECT_FALSE(rules.validMove(i, p2, board));
    }
    EXPECT_EQ(board.stores.at(p1) + board.stores.at(p2), 6 * 6 * 2);
}
