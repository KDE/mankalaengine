#include <bohnenspielrules.h>
#include <gtest/gtest.h>

TEST(BohnenspielRules, ValidMove) {
    BohnenspielBoard board;
    BohnenspielRules rules;
    Player p1 = first_player;
    Player p2 = second_player;

    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(rules.validMove(i, p1, board));
        EXPECT_TRUE(rules.validMove(i, p2, board));
    }
}

TEST(BohnenspielRules, InvalidMove) {
    BohnenspielBoard board;
    std::vector<int> p1_holes(6, 0);
    board.holes.insert(board.holes.begin(), p1_holes.begin(), p1_holes.end());
    BohnenspielRules rules;
    Player p1 = first_player;
    Player p2 = second_player;

    for (int i = 0; i < 6; ++i) {
        EXPECT_FALSE(rules.validMove(i, p1, board));
        EXPECT_TRUE(rules.validMove(i, p2, board));
    }
}

TEST(BohnenspielRules, SimpleMove) {
    BohnenspielBoard board;
    BohnenspielBoard next_board;
    BohnenspielRules rules;
    Player p1 = first_player;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) += 1;
    next_board.holes.at(2) += 1;
    next_board.holes.at(3) += 1;
    next_board.holes.at(4) += 1;
    next_board.holes.at(5) += 1;
    next_board.holes.at(6) += 1;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(board.holes.at(i), next_board.holes.at(i));
    }
}

TEST(BohnenspielRules, LapMove) {
    BohnenspielBoard board;
    BohnenspielBoard next_board;
    BohnenspielRules rules;
    Player p2 = second_player;

    next_board.holes.at(8) = 0;
    next_board.holes.at(9) += 1;
    next_board.holes.at(10) += 1;
    next_board.holes.at(11) += 1;
    next_board.holes.at(0) += 1;
    next_board.holes.at(1) += 1;
    next_board.holes.at(2) += 1;

    rules.move(2, p2, board);
    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(board.holes.at(i), next_board.holes.at(i));
    }
}

TEST(BohnenspielRules, MoveWithSingleCapture) {
    BohnenspielBoard board;
    BohnenspielBoard next_board;
    BohnenspielRules rules;
    Player p1 = first_player;

    board.holes = std::vector<int>(12, 0);
    next_board.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 1;
    board.holes.at(1) = 1;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) = 0;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(board.holes.at(i), next_board.holes.at(i));
    }
    EXPECT_EQ(board.stores.at(0), 2);
    EXPECT_EQ(board.stores.at(1), 0);
}

TEST(BohnenspielRules, MoveWithMultipleCaptures) {
    BohnenspielBoard board;
    BohnenspielBoard next_board;
    BohnenspielRules rules;
    Player p1 = first_player;

    board.holes = std::vector<int>(12, 0);
    next_board.holes = std::vector<int>(12, 0);

    board.holes.at(0) = 1;
    board.holes.at(1) = 1;
    board.holes.at(2) = 2;

    next_board.holes.at(0) = 0;
    next_board.holes.at(1) = 0;
    next_board.holes.at(1) = 0;

    rules.move(0, p1, board);
    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(board.holes.at(i), next_board.holes.at(i));
    }
    EXPECT_EQ(board.stores.at(0), 4);
    EXPECT_EQ(board.stores.at(1), 0);
}

TEST(BohnenspielRules, CaptureWithLap) {
    BohnenspielBoard board;
    BohnenspielBoard next_board;
    BohnenspielRules rules;
    Player p2 = second_player;

    board.holes.at(8) = 1;
    board.holes.at(9) = 1;
    board.holes.at(10) = 2;
    board.holes.at(11) = 4;
    board.holes.at(0) = 6;
    board.holes.at(1) = 2;
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
        EXPECT_EQ(board.holes.at(i), next_board.holes.at(i));
    }
    EXPECT_EQ(board.stores.at(0), 0);
    EXPECT_EQ(board.stores.at(1), 16);
}
