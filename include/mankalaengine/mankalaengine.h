#include <functional>
#include <rules.h>

namespace MankalaEngine {

class MankalaEngine {
    std::function<int(Player player, const Rules&, const Board&)> _selectMove;

  public:
    MankalaEngine(
        std::function<int(Player, const Rules&, const Board&)> selectMove)
        : _selectMove(std::move(selectMove)) {}

    bool play(Player player, const Rules& rules, Board& state);
};

} // namespace MankalaEngine
