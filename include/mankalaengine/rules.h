#pragma once

#include <array>
#include <vector>

namespace MankalaEngine {

enum Player { first_player, second_player };

struct Board {
    std::vector<int> holes;
    std::array<int, 2> stores = {0};
};

class Rules {
    int _player_holes;

  protected:
    int position(int move, Player player) const {
        return player * _player_holes + move;
    }

  public:
    Rules(int player_holes) : _player_holes(player_holes) {}
    int player_holes() const { return _player_holes; }

    virtual void move(int move, Player player, Board &state) const = 0;
    virtual bool validMove(int move, Player player,
                           const Board &state) const = 0;

    virtual ~Rules() = default;
};

} // namespace MankalaEngine
