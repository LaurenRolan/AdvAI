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

    // Iteratively increase depth limit until solution is found
    for (char max_depth = 0; ; ++max_depth) {
        set<long long> closed; // Fresh closed set for each depth limit

        // Begin depth-limited search from the root node
        Node n0 = make_root_node(s0_state);
        bool found = depth_limited_search(n0, puzzle_size, max_depth, result, closed);

        if (found) {
            result.stop_timer();
            return result;
        }
    }
}
#include <iostream>

// Updated recursive function to include detailed debug and check depth precautions
bool IDFS::depth_limited_search(Node n, char puzzle_size, char max_depth, Result &result, set<long long> &closed) {
    // Prevent exceeding the maximum depth
    if (n.depth > max_depth) {
        return false;
    }

    // Increase the number of expanded nodes
    result.increase_expanded();

    // Log current state and depth
    // cout << "Visiting node at depth: " << (int)n.depth << " with state: " << n.state.CompressedState << endl;

    // Check if current state is the goal
    if (is_goal(n.state, puzzle_size)) {
        result.set_optimal_lenght(n.g);
        return true;
    }

    // Ensure we do not exceed the depth limit specified
    if ((int)n.depth >= (int)max_depth) {
        return false;
    }

    // Insert current state into the closed set
    closed.insert(n.state.CompressedState);

    // Retrieve successors
    vector<tuple<long long, char>> successors = succ(n, n.action, puzzle_size);

    // Log number of successors
    // cout << "Number of successors: " << successors.size() << endl;

    for (const auto &successor : successors) {
        long long state = get<0>(successor);
        char action = get<1>(successor);

        // Process only new states that are not in the closed set
        if (closed.find(state) == closed.end()) {
            Node next_node = make_node_with_depth(n.g, state, action, puzzle_size, n.index, n.depth + 1);

            // Log next node depth and state
            // cout << "Exploring successor with state: " << state << " at depth: " << (int)(n.depth + 1) << endl;

            // Increase the number of generated nodes
            result.increase_generated();

            // Recursive call
            if (depth_limited_search(next_node, puzzle_size, max_depth, result, closed)) {
                return true;
            }
        } else {
            // Log skipped state due to being in the closed set
            // cout << "State " << state << " already in closed set, skipping." << endl;
        }
    }

    // Backtrack: remove the current state from the closed set
    closed.erase(n.state.CompressedState);

    return false;
}