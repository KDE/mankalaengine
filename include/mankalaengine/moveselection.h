#pragma once

#include <rules.h>

namespace MankalaEngine {

int random(Player player, const Rules& rules, const Board& state);

int miniMax(Player player, const Rules& rules, const Board& state);

} // namespace MankalaEngine
