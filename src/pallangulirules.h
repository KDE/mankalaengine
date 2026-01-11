/*
    SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <mankalaengine_export.h>
#include <rules.h>

// C++
#include <memory>

namespace MankalaEngine {

/**
 * @brief The board for the Pallanguli Mancala variation.
 *
 * Pallanguli is played on a board with 2 rows, each with 7 holes, and 2
 * stores. Each player owns the store to their right hand and controls the holes
 * on their side of the board. At the beginning, all holes are filled with 6
 * counters.
 */
struct MANKALAENGINE_EXPORT PallanguliBoard : Board {
    PallanguliBoard() { holes = std::vector<int>(14, 6); }
};

/**
 * @brief The rules for the Pallanguli Mancala variation.
 */
class MANKALAENGINE_EXPORT PallanguliRules : public Rules {
    /**
     * @brief Represents the PallanguliRules private internal implementation
     * details.
     */
    struct PallanguliRulesImpl;

    /**
     * @brief PallanguliRules private internal implementation details.
     */
    std::unique_ptr<PallanguliRulesImpl> _impl;

  public:
    /**
     * @brief Class constructor.
     */
    PallanguliRules();

    /**
     * @brief Plays a move.
     *
     * In Pallanguli, moves follow these rules:
     * 1. Player picks up all counters from a pit and sows them anticlockwise
     * 2. Capture rules:
     *    - If sowing results in a pit containing exactly 4 counters, they are
     *      immediately captured
     *    - If the last counter falls into a pit where the next pit is empty but
     *      the pit beyond contains counters, those counters are captured
     * 3. Turn ends if:
     *    - The last counter falls into a pit where the next two pits are empty
     *    - There are no more valid moves
     * 4. If turn continues, player starts from the next non-empty pit
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     */
    void move(int move, Player player, Board& state) const override;

    /**
     * @brief Checks if a move breaks the rules.
     *
     * In Pallanguli, any move between 0 and 6 is valid, as long as there are
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
    PallanguliRules(const PallanguliRules& other);

    /**
     * @brief Move constructor.
     */
    PallanguliRules(PallanguliRules&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    PallanguliRules& operator=(const PallanguliRules& other);

    /**
     * @brief Move assignment.
     */
    PallanguliRules& operator=(PallanguliRules&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    ~PallanguliRules() override;
};

} // namespace MankalaEngine
