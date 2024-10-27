#include "../include/algorithms.h"
#include <stack>
#include <set>

using namespace std;

Result IDFS::run(deque<char> s0, char puzzle_size) {
    Result result;
    result.start_timer();

    // Iteratively increase depth until the goal is found
    for (char max_depth = 0; ; ++max_depth) {
        set<long long> closed;
        stack<Node> open;

        // Initialize the root node and state
        State s0_state = init(s0, puzzle_size);
        if (is_goal(s0_state, puzzle_size)) {
            result.stop_timer();
            result.set_optimal_lenght(0);
            result.set_h_initial(s0_state.h);
            result.increase_h(s0_state.h);
            return result;
        }

        // Push the initial node onto the stack with depth = 0
        Node n0 = make_root_node(s0_state); // Assuming depth starts at 0
        open.push(n0);

        while (!open.empty()) {
            Node n = open.top();
            open.pop();
            result.increase_expanded();

            // Check if goal is reached
            if (is_goal(n.state, puzzle_size)) {
                result.stop_timer();
                result.set_optimal_lenght(n.g);
                return result;
            }

            // Depth limit check
            if (n.depth >= max_depth) continue;

            // Add the current state to the closed set to prevent revisiting it within this depth level
            closed.insert(n.state.CompressedState);

            // Generate successors
            vector<tuple<long long, char>> successors = succ(n, n.action, puzzle_size);
            for (auto& successor : successors) {
                long long state = get<0>(successor);
                char action = get<1>(successor);

                // Only consider successors that haven’t been visited in this iteration
                if (closed.find(state) == closed.end()) {
                    Node n_line = make_node(n.g, state, action, puzzle_size, n.depth + 1); // Increase depth by 1
                    result.increase_generated();
                    open.push(n_line);
                }
            }
        }
    }

    result.stop_timer();
    result.set_h_total(-1);
    return result; // In case no solution is found
}
