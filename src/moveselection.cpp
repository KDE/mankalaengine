#include <cstdlib>
#include <limits>
#include <moveselection.h>

namespace MankalaEngine {

int _eval(const Board& state) {
    return state.stores.at(player_1) - state.stores.at(player_2);
}

int _miniMax(Player player, const Rules& rules, const Board& state, int depth) {
    if (depth == 0 || rules.gameOver(player, state)) {
        return _eval(state);
    }

    auto moves = rules.getMoves(player, state);
    Board new_state = state;

    if (player == player_1) {
        int highest_eval = std::numeric_limits<int>::min(); // Negative infinity
        for (const auto& move : moves) {
            rules.move(move, player, new_state);
            int eval = _miniMax(player_2, rules, new_state, depth - 1);
            highest_eval = std::max(highest_eval, eval);
            new_state = state; // Undo previous move
        }
        return highest_eval;
    }

    int lowest_eval = std::numeric_limits<int>::max(); // Positive infinity
    for (const auto& move : moves) {
        rules.move(move, player, new_state);
        int eval = _miniMax(player_1, rules, new_state, depth - 1);
        lowest_eval = std::min(lowest_eval, eval);
        new_state = state; // Undo previous move
    }
    return lowest_eval;
}

int random(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }
    return moves.at(std::rand() % moves.size());
}

int miniMax(Player player, const Rules& rules, const Board& state) {
    const std::vector<int> moves = rules.getMoves(player, state);
    if (moves.empty()) {
        return -1;
    }
    int chosen_move = -1;

    if (player == player_1) {
        int highest_eval = std::numeric_limits<int>::min(); // Negative infinity
        for (const auto& move : moves) {
            int eval = _miniMax(player, rules, state, 5);
            if (eval > highest_eval) {
                highest_eval = eval;
                chosen_move = move;
            }
        }
    } else {
        int lowest_eval = std::numeric_limits<int>::max(); // Positive infinity
        for (const auto& move : moves) {
            int eval = _miniMax(player, rules, state, 5);
            if (eval < lowest_eval) {
                lowest_eval = eval;
                chosen_move = move;
            }
        }
    }

    return chosen_move;
}

} // namespace MankalaEngine
