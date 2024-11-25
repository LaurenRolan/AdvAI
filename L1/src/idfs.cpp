// Implementação do algoritmo IDFS

#include "../include/algorithms.h"
#include <set>
#include <deque>
#include <iostream>

using namespace std;

Result IDFS::run(deque<char> s0, char puzzle_size) {
    Result result;
    result.start_timer();

    State s0_state = init(s0, puzzle_size);

    Node n0 = make_root_node(s0_state);
    result.set_h_initial(s0_state.h);

    // increase depth limit until finds goal
    for (int max_depth = 0; ; max_depth++) {

        bool found = depth_limited_search(n0, puzzle_size, max_depth, result);

        if (found) {
            result.stop_timer();
            return result;
        }
    }
}

bool IDFS::depth_limited_search(Node n, char puzzle_size, int max_depth, Result &result)
{
    if (is_goal(n.state, puzzle_size)) {
        result.set_optimal_lenght(n.g);
        return true;
    }

    if (max_depth == 0) {
        return false;
    }

    result.increase_expanded();
    auto successors = succ(n, n.action, puzzle_size);

    for (auto successor : successors) {
        long long state = get<0>(successor);
        char action = get<1>(successor);

        Node next_node = make_node(n.g, state, action, puzzle_size, 0);

        result.increase_generated();
        if (depth_limited_search(next_node, puzzle_size, max_depth - 1, result)) {
            return true;
        }
    }

    return false;
}