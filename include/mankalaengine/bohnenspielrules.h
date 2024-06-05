#pragma once

#include <rules.h>

namespace MankalaEngine {

struct BohnenspielBoard : Board {
    BohnenspielBoard() { holes = std::vector<int>(12, 6); }
};

class BohnenspielRules : public Rules {
    void try_capture(int position, Player player, Board &state) const;

  public:
    BohnenspielRules() : Rules(6) {}

    void move(int move, Player player, Board &state) const override;
    bool validMove(int move, Player player, const Board &state) const override;
};

} // namespace MankalaEngine
