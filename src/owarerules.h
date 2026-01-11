/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "mankalaengine_export.h"
#include "rules.h"

// C
#include <memory.h>

namespace MankalaEngine {

/**
 * @brief The board for the Oware Mancala variation.
 *
 * Oware is played on a board with 2 rows, each with 6 holes, and 2
 * stores. Each player owns the store to their right hand and controls the holes
 * on their side of the board. At the beginning, all holes are filled with 4
 * counters.
 */
struct MANKALAENGINE_EXPORT OwareBoard : Board {
    OwareBoard() { holes = std::vector<int>(12, 4); }
};

/**
 * @brief The rules for the Oware Mancala variation.
 */
class MANKALAENGINE_EXPORT OwareRules : public Rules {
    /**
     * @brief Represents the OwareRules private internal implementation
     * details.
     */
    struct OwareRulesImpl;

    /**
     * @brief OwareRules private internal implementation details.
     */
    std::unique_ptr<OwareRulesImpl> _impl;

  public:
    /**
     * @brief Class constructor.
     */
    OwareRules();

    /**
     * @brief Plays a move.
     *
     * In Oware, a move consists of a player picking up all the pebbles in
     * a hole and going through the holes next to the chosen one anticlockwise,
     * placing one counter in each one until they have no more counters in their
     * hand.
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     */
    void move(int move, Player player, Board& state) const override;

    /**
     * @brief Finishes the game.
     *
     * Moves all the remaining pebbles in the holes to the winner's store.
     *
     * @param player The player whose turn ended the game.
     * @param state The board in which the game is being played.
     */
    void finishGame(Player player, Board& state) const override;

    /**
     * @brief Checks if a move breaks the rules.
     *
     * In Oware, any move between 0 and 5 is valid, as long as there are
     * pebbles in the hole
     *
     * @param player The player whose turn it is to play.
     * @param pos The move to be played.
     * @param state The board in which the move is going to be played.
     *
     * @returns True if the move can be played, false otherwise.
     */
    bool isValidMove(int pos, Player player, const Board& state) const override;

    /**
     * @brief Checks if the game has ended.
     *
     * In Oware, a game ends when a player has 25 or more counters in their
     * store or when a player has no more valid moves.
     *
     * @param player The player whose turn it is to play.
     * @param state The board in which the game is being played.
     *
     * @returns True if the game is finished, false otherwise.
     */
    bool isGameOver(Player player, const Board& state) const override;

    /**
     * @brief Copy constructor.
     */
    OwareRules(const OwareRules& other);

    /**
     * @brief Move constructor.
     */
    OwareRules(OwareRules&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    OwareRules& operator=(const OwareRules& other);

    /**
     * @brief Move assignment.
     */
    OwareRules& operator=(OwareRules&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    ~OwareRules() override;
};

} // namespace MankalaEngine
