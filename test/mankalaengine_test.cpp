#include <bohnenspielrules.h>
#include <gtest/gtest.h>
#include <mankalaengine.h>
#include <moveselection.h>

TEST(MankalaEngine, RandomSelectionFullGame) {
    MankalaEngine::MankalaEngine engine(MankalaEngine::random);
    MankalaEngine::BohnenspielBoard board;
    MankalaEngine::BohnenspielRules rules;
    MankalaEngine::Player p1 = MankalaEngine::first_player;
    MankalaEngine::Player p2 = MankalaEngine::second_player;
    bool p1_can_play = true;
    bool p2_can_play = true;

    while (p1_can_play && p2_can_play) {
        p1_can_play = engine.play(p1, rules, board);
        p2_can_play = engine.play(p2, rules, board);
    }

    int holes = rules.player_holes();
    for (int i = 0; i < holes; ++i) {
        if (!p1_can_play) {
            EXPECT_FALSE(rules.validMove(i, p1, board));
        }
        if (!p2_can_play) {
            EXPECT_FALSE(rules.validMove(i, p2, board));
        }
    }
}
