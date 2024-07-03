/*
    SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <rules.h>

namespace MankalaEngine {

int user(Player player, const Rules& rules, const Board& state);

int random(Player player, const Rules& rules, const Board& state);

int miniMax(Player player, const Rules& rules, const Board& state);

int mtdf(Player player, const Rules& rules, const Board& state);

} // namespace MankalaEngine
