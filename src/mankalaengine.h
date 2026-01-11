/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "mankalaengine_export.h"
#include "rules.h"

// C++
#include <functional>

// C
#include <memory.h>

namespace MankalaEngine {

/**
 * @brief Used to generate, choose and play moves for any Mancala variant.
 */
class MANKALAENGINE_EXPORT MankalaEngine {
    /**
     * @brief Represents the MankalaEngine private internal implementation
     * details.
     */
    struct MankalaEngineImpl;

    /**
     * @brief MankalaEngine private internal implementation details.
     */
    std::unique_ptr<MankalaEngineImpl> _impl;

  public:
    /**
     * @brief Class constructor.
     *
     * @param selectMove The move selection function to be used.
     *
     * @see moveselection.h
     */
    explicit MankalaEngine(
        std::function<int(Player, const Rules&, const Board&)> selectMove);

    /**
     * @brief Play a move.
     *
     * Chooses and plays a move for the player specified, updating the board.
     * Before playing, it checks if the game is over according to the rules. If
     * that's the case, it finishes the game and returns false. Returns true if
     * it was possible to play a move.
     *
     * @param player The player whose turn it is to play.
     * @param rules The rules to use when playing.
     * @param state The board in which the move will be played.
     *
     * @returns False if the player can't play, true otherwise.
     *
     * @see Player Rules Board
     */
    bool play(Player player, const Rules& rules, Board& state) const;

    /**
     * @brief Copy constructor.
     */
    MankalaEngine(const MankalaEngine& other);

    /**
     * @brief Move constructor.
     */
    MankalaEngine(MankalaEngine&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    MankalaEngine& operator=(const MankalaEngine& other);

    /**
     * @brief Move assignment.
     */
    MankalaEngine& operator=(MankalaEngine&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    ~MankalaEngine();
};

} // namespace MankalaEngine
