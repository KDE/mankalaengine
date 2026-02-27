/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include "variantdescriptions.h"

#include "mankalaengine_export.h"

// Qt
#include <QtCore/QString>

// C++
#include <array>
#include <memory>
#include <vector>

namespace MankalaEngine {

/**
 * @brief Used to define the two players that play a game.
 */
enum MANKALAENGINE_EXPORT Player { player_1, player_2 };

/**
 * @brief Used to define the board in which the game is played.
 *
 * Defines a general Mancala board, concrete variants should inherit from this
 * struct to define their own boards.
 */
struct MANKALAENGINE_EXPORT Board {

    /**
     * @brief The board holes.
     *
     * Array representing the holes in a board. Each index represents a hole,
     * and its value represents the amount of pebbles in said hole. The first
     * half of the array corresponds to the holes controlled by player 1 and the
     * second half to the holes controlled by player 2.
     */
    std::vector<int> holes;

    /**
     * @brief The board stores.
     *
     * Array representing the stores in a board. The first element of the array
     * corresponds to the store owned by player 1 and the second element to the
     * store owned by player 2.
     */
    std::array<int, 2> stores = {0};
};

/**
 * @brief Used to define the rules for a variant.
 *
 * Defines an interface for the variant rules, concrete variants should inherit
 * from this class to define their own rulesets. See the bohnenspielrules
 * implementation for an example of how to use this class to define the rules of
 * a variant.
 *
 * @see bohnenspielrules.h bohnenspielrules.cpp
 */
class MANKALAENGINE_EXPORT Rules {

    /**
     * @brief Represents the Rules private internal implementation details.
     */
    struct RulesImpl;

    /**
     * @brief Rules private internal implementation details.
     */
    std::unique_ptr<RulesImpl> _impl;

  protected:
    /**
     * @brief Calculates the index on the holes array corresponding to a move.
     *
     * @param move The move to translate to an index.
     * @param player The player that played.
     *
     * @returns The index corresponding to the move.
     */
    int position(int move, Player player) const {
        return player * player_holes() + move;
    }

  public:
    /**
     * @brief Class constructor.
     *
     * Used for specifying a new ruleset without providing a description for it.
     *
     * @param player_holes The amount of holes each player controls.
     */
    Rules(int player_holes);

    /**
     * @brief Class constructor.
     *
     * @param player_holes The amount of holes each player controls.
     * @param description This variant's description.
     */
    Rules(int player_holes, QString description);

    /**
     * @brief Gets the amount of holes each player controls.
     *
     * @returns The amount of holes each player controls.
     */
    int player_holes() const;

    /**
     * @brief Gets the description of this variant's rules.
     *
     * @returns The description of this variant's rules.
     */
    QString description() const;

    /**
     * @brief Calculate all possible moves.
     *
     * Calculates all the moves a player can play in a certain board
     * configuration.
     *
     * @param player The player whose turn it is to play.
     * @param state The board in which the player is playing.
     *
     * @returns An array with all the possible moves for the player.
     */
    std::vector<int> getMoves(Player player, const Board& state) const;

    /**
     * @brief Finishes the game.
     *
     * Performs any actions that should be done after the game ended, such as
     * moving all the remaining pebbles in the holes to the winner's store, for
     * example.
     *
     * @param player The player whose turn ended the game.
     * @param state The board in which the game is being played.
     */
    virtual void finishGame(Player player, Board& state) const;

    /**
     * @brief Checks if the game has ended.
     *
     * @param player The player whose turn it is to play.
     * @param state The board in which the game is being played.
     *
     * @returns True if the game is finished, false otherwise.
     */
    virtual bool isGameOver(Player player, const Board& state) const;

    /**
     * @brief Plays a move.
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     */
    virtual void move(int move, Player player, Board& state) const = 0;

    /**
     * @brief Checks if a move breaks the rules.
     *
     * @param player The player whose turn it is to play.
     * @param move The move to be played.
     * @param state The board in which the move is going to be played.
     *
     * @returns True if the move can be played, false otherwise.
     */
    virtual bool isValidMove(int move, Player player,
                             const Board& state) const = 0;

    /**
     * @brief Copy constructor.
     */
    Rules(const Rules& other);

    /**
     * @brief Move constructor.
     */
    Rules(Rules&& other) noexcept;

    /**
     * @brief Copy assignment.
     */
    Rules& operator=(const Rules& other);

    /**
     * @brief Move assignment.
     */
    Rules& operator=(Rules&& other) noexcept;

    /**
     * @brief Class destructor.
     */
    virtual ~Rules();
};

} // namespace MankalaEngine
