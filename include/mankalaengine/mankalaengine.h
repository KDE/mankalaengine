#include <functional>
#include <rules.h>

namespace MankalaEngine {

/**
 * @brief Used to generate, choose and play moves for any Mancala variant.
 */
class MankalaEngine {
    std::function<int(Player player, const Rules&, const Board&)> _selectMove;

  public:
    /**
     * @brief Class constructor.
     *
     * @param selectMove The move selection function to be used.
     *
     * @see moveselection.h
     */
    explicit MankalaEngine(
        std::function<int(Player, const Rules&, const Board&)> selectMove)
        : _selectMove(std::move(selectMove)) {}

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
    bool play(Player player, const Rules& rules, Board& state);
};

} // namespace MankalaEngine
