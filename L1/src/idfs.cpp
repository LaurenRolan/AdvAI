#include "../include/algorithms.h"
#include <set>
#include <deque>

using namespace std;

Result IDFS::run(deque<char> s0, char puzzle_size) {
    Result result;
    result.start_timer();

    State s0_state = init(s0, puzzle_size);
    if (is_goal(s0_state, puzzle_size)) {
        result.stop_timer();
        result.set_optimal_lenght(0);
        result.set_h_initial(s0_state.h);
        result.increase_h(s0_state.h);
        return result;
    }

    Node n0 = make_root_node(s0_state);

    // increase depth limit until finds goal
    for (char max_depth = 0; ; ++max_depth) {

        bool found = depth_limited_search(n0, puzzle_size, max_depth, result);

        if (found) {
            result.stop_timer();
            return result;
        }
    }
}
#include <iostream>

bool IDFS::depth_limited_search(Node n, char puzzle_size, char max_depth, Result &result) {
    if (n.depth > max_depth) {
        return false;
    }

    result.increase_expanded();

    // cout << "Visiting node at depth: " << (int)n.depth << " with state: " << n.state.CompressedState << endl;

    if (is_goal(n.state, puzzle_size)) {
        result.set_optimal_lenght(n.g);
        return true;
    }


    vector<tuple<long long, char>> successors = succ(n, n.action, puzzle_size);
    // cout << "Number of successors: " << successors.size() << endl;

    for (const auto &successor : successors) {
        // checar se sucessor é = pai do nodo, se for nao gerar -> aparentemente não repetimos a última ação
        long long state = get<0>(successor);

        char action = get<1>(successor);

            Node next_node = make_node_with_depth(n.g, state, action, puzzle_size, n.index, n.depth + 1);

            // cout << "Exploring successor with state: " << state << " at depth: " << (int)(n.depth + 1) << endl;

            result.increase_generated();
            result.increase_h(next_node.state.h);
            if (depth_limited_search(next_node, puzzle_size, max_depth, result)) {
                return true;
            }
    }

    return false;
}