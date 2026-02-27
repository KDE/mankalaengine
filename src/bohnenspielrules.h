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
 * @brief The board for the Bohnenspiel Mancala variation.
 *
 * Bohnenspiel is played on a board with 2 rows, each with 6 holes, and 2
 * stores. Each player owns the store to their right hand and controls the holes
 * on their side of the board. At the beginning, all holes are filled with 6
 * counters.
 */
struct MANKALAENGINE_EXPORT BohnenspielBoard : Board {
    BohnenspielBoard() { holes = std::vector<int>(12, 6); }
};

/**
 * @brief The rules for the Bohnenspiel Mancala variation.
 */
class MANKALAENGINE_EXPORT BohnenspielRules : public Rules {
    /**
     * @brief Represents the BohnenspielRules private internal implementation
     * details.
     */
    struct BohnenspielRulesImpl;

    /**
     * @brief BohnenspielRules private internal implementation details.
     */
    std::unique_ptr<BohnenspielRulesImpl> _impl;

  public:
    /**
     * @brief Class constructor.
     */
    BohnenspielRules();

    /**
     * @brief Plays a move.
     *
     * In Bohnenspiel, a move consists of a player picking up all the pebbles in
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
     * @brief Checks if a move breaks the rules.
     *
     * In Bohnenspiel, any move between 0 and 5 is valid, as long as there are
     * pebbles in the hole.
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     *
     * @returns True if the move can be played, false otherwise.
     */
    bool isValidMove(int move, Player player,
                     const Board& state) const override;

    /**
     * @brief Copy constructor.
     */
    BohnenspielRules(const BohnenspielRules& other);

    /**
     * @brief Move constructor.
     */
    BohnenspielRules(BohnenspielRules&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    BohnenspielRules& operator=(const BohnenspielRules& other);

    /**
     * @brief Move assignment.
     */
    BohnenspielRules& operator=(BohnenspielRules&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    ~BohnenspielRules() override;
};

} // namespace MankalaEngine
