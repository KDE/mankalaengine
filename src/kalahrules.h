/*
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
    SPDX-FileCopyrightText: 2025 Benson Muite <benson_muite@emailplus.org>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "mankalaengine_export.h"
#include "rules.h"

// C++
#include <memory>

// C
#include <memory.h>

namespace MankalaEngine {

/**
 * @brief The board for the Kalah Mancala variation.
 *
 * Kalah is played on a board with 2 rows, each with 6 holes, and 2
 * stores. Each player owns the store to their right hand and controls the holes
 * on their side of the board. At the beginning, all holes are filled with 6
 * counters and the stores are empty.
 */
struct MANKALAENGINE_EXPORT KalahBoard : Board {
    KalahBoard() { holes = std::vector<int>(12, 6); }
};

/**
 * @brief The rules for the Kalah Mancala variation.
 */
class MANKALAENGINE_EXPORT KalahRules : public Rules {
    /**
     * @brief Represents the KalahRules private internal implementation details
     */
    struct KalahRulesImpl;

    /**
     * @brief KalahRules private internal implementation details
     */
    std::unique_ptr<KalahRulesImpl> _impl;

  public:
    /**
     * @brief Class Constructor
     */
    KalahRules();

    /**
     * @brief Plays a move.
     *
     * In Kalah, a move consists of a player picking up all the pebbles in
     * a hole and going through the holes next to the chosen one anticlockwise,
     * placing one counter in each one including their own store until they have
     * no more counters in their hand.
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     */
    void move(int pos, Player player, Board& state) const override;

    /**
     * @brief Checks if a move breaks the rules.
     *
     * In Kalah, any move between 0 and 5 is valid, as long as there are
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
     * In Kalah, a game ends when a player has 37 or more counters in their
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
    KalahRules(const KalahRules& other);

    /**
     * @brief Move constructor.
     */
    KalahRules(KalahRules&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    KalahRules& operator=(const KalahRules& other);

    /**
     * @brief Move assignment.
     */
    KalahRules& operator=(KalahRules&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    ~KalahRules() override;
};

} // namespace MankalaEngine
