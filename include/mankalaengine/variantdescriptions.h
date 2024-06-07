#pragma once

#define PLACEHOLDER_DESCRIPTION "No description was provided for this variant."

#define BOHNENSPIEL_DESCRIPTION                                                \
    "Bohnenspiel is played on a board with 2 rows,"                            \
    " each with 6 holes, and 2 end-holes, called stores."                      \
    " Each player owns the store to their right hand and controls"             \
    " the holes on their side of the board.\n"                                 \
    "At the beginning, all holes are filled with 6 counters."                  \
    " The starting player chooses one of the holes under their"                \
    " control and removes all counters in it."                                 \
    " The player goes through the holes next to the chosen one"                \
    " anticlockwise, placing one counter in each one until they"               \
    " have no more counters in their hand. Both stores are skipped."           \
    " This is called sowing.\nIf the last counter falls into a hole,"          \
    " bringing the total number of counters in the hole to 2, 4, or 6,"        \
    " these counters are captured and put in the player's store."              \
    " When a capture is made, the preceding hole is checked and"               \
    " captured according to the same rule. The captures are repeated"          \
    " until the previous hole has some number of counters other than"          \
    " 2, 4, or 6.\nThe game ends when a player cannot move anymore;"           \
    " the remaining seeds on the board are given to the opposing player,"      \
    " and the winner is the one with more seeds."
