/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
    SPDX-FileCopyrightText: 2025 Rishav Ray Chaudhury <rrcemon@gmail.com>
    SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
    SPDX-FileCopyrightText: 2025 Benson Muite <benson_muite@emailplus.org>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <KLocalizedString>

// Qt
#include <QtCore/QString>

namespace MankalaEngine {

inline QString placeholderDescription() {
    return i18n("No description was provided for this variant.");
}

inline QString bohnenspielDescription() {
    return i18n(
        "Bohnenspiel is played on a board with 2 rows,"
        " each with 6 holes, and 2 end-holes, called stores."
        " Each player owns the store to their right hand and controls"
        " the holes on their side of the board.\n"
        "At the beginning, all holes are filled with 6 counters."
        " The starting player chooses one of the holes under their"
        " control and removes all counters in it."
        " The player goes through the holes next to the chosen one"
        " anticlockwise, placing one counter in each one until they"
        " have no more counters in their hand. Both stores are skipped."
        " This is called sowing.\nIf the last counter falls into a hole,"
        " bringing the total number of counters in the hole to 2, 4, or 6,"
        " these counters are captured and put in the player's store."
        " When a capture is made, the preceding hole is checked and"
        " captured according to the same rule. The captures are repeated"
        " until the previous hole has some number of counters other than"
        " 2, 4, or 6.\nThe game ends when a player cannot move anymore;"
        " the remaining seeds on the board are given to the opposing player,"
        " and the winner is the one with more seeds.");
}

inline QString owareDescription() {
    return i18n(
        "Oware is played on a board with 2 rows,"
        " each with 6 holes, and 2 end-holes, called stores."
        " Each player owns the store to their right hand and controls"
        " the holes on their side of the board.\n"
        "At the beginning, all holes are filled with 4 counters."
        " The starting player chooses one of the holes under their"
        " control and removes all counters in it."
        " The player goes through the holes next to the chosen one"
        " anticlockwise, placing one counter in each one until they"
        " have no more counters in their hand. Both stores are skipped and"
        " the starting hole is always left empty, so it will also be skipped"
        " if there were 12 or more counters inside it. This is called sowing.\n"
        "If the last counter falls into a hole controlled by the opponent,"
        " bringing the total number of counters in the hole to 2 or 3,"
        " these counters are captured and put in the player's store. When"
        " a capture is made, the preceding hole is checked and captured"
        " according to the same rule. The captures are repeated until"
        " the previous hole does not belong to the opponent or it has some "
        "number"
        " of counters other than 2 or 3. The only exception to this is when a "
        "Grand"
        " Slam occurs. A Grand Slam is a move that would capture all of the"
        " opponent's counters, and in this case no counters are captured,"
        " as this would prevent the opponent from continuing the game.\n"
        "This is related to a more general rule, that states that a player"
        " should make moves that allow the opponent to continue playing. If"
        " the opponent's holes are all empty, the player should make a move"
        " that places pebbles in the opponent's side of the board. If no such"
        " move is possible, the current player captures all seeds in their own"
        " territory, ending the game.\n"
        "The game ends when a player has 25 or more counters in their store.");
}

inline QString pallanguliDescription() {
    return i18n(
        "Pallanguli is played with a rectangular board that has two rows and 7"
        " pits on each side, along with pebbles/coins.\n"
        "To begin, each pit is filled with 6 coins (the number of coins "
        "varies)."
        " The first player picks up coins from one of the pits and starts to "
        "drop"
        " them in an anti-clockwise direction in each succeeding pit."
        " If the player reaches the last pit in the row, he/she continues on "
        "their"
        " opponent's side."
        " Once the last coin is dropped, the player takes the coin from the "
        "next"
        " pit and continues playing in the same way."
        " If the last coin falls into a pit where the next pit is empty,"
        " the coins in the pit beyond the empty pit are captured and stored by "
        "the"
        " player."
        " The player continues playing from the next cup containing coins."
        " If the last coin falls into a pit with two empty holes beyond, the"
        " player's turn comes to an end."
        " The opponent now continues to play in the same way, taking coins "
        "from any"
        " of their pits and going around dropping the coins in a "
        "counter-clockwise"
        " direction."
        " If, after dropping a pebble into a pit, the pit contains four coins,"
        " these coins are also captured by the player.\n"
        "The round is over when no coins remain.");
}

inline QString kalahDescription() {
    return i18n(
        "Kalah is played on a board with 2 rows,"
        " each with 6 holes, and 2 end-holes, called kalahs."
        " Each player owns the store to their right hand and controls"
        " the holes on their side of the board.\n"
        "At the beginning, all holes are filled with 6 beans"
        "  and the kalahs are empty."
        " The starting player chooses one of the holes on their side"
        " and removes all the beans in it."
        " The player goes through the holes next to the chosen one "
        " anticlockwise, placing one bean in each one until they"
        " have no more beans left. The opponent's kalah is skipped."
        " This is called sowing. If after sowing, the last bean"
        " falls in the player's kalah, the player must move again."
        " Otherwise, the move is over.\n"
        "If the last bean falls into an empty hole controlled"
        " by the player and the hole controlled by the"
        " opponent opposite to it has beans in it, then all the"
        " beans in both the holes are removed and moved to the"
        " player's kalah. This is called capturing.\n"
        "The game ends when a player has more than 36 beans in their kalah.");
}

} // namespace MankalaEngine
