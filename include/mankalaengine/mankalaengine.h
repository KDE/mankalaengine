#include <functional>
#include <rules.h>

namespace MankalaEngine {

class MankalaEngine {
    std::function<int(const std::vector<int> &, Board &)> _selectMove;
    std::vector<int> getMoves(const Rules &rules, Player player, Board &state);

  public:
    MankalaEngine(
        std::function<int(const std::vector<int> &, Board &)> selectMove)
        : _selectMove(std::move(selectMove)) {}

    bool play(const Rules &rules, Player player, Board &state);
};

} // namespace MankalaEngine
