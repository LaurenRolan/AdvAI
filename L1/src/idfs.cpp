#include "../include/algorithms.h"
#include <set>

using namespace std;

Result IDFS::run(deque<char> s0, char puzzle_size)
{
    Result result;
    set<long long> closed;
    deque<Node> open;
    char depth = 0;
    bool found = false;

    result.start_timer();
    State s0_state = init(s0, puzzle_size);
    if(is_goal(s0_state, puzzle_size))
    {
        result.stop_timer();
        result.set_optimal_lenght(0);
        result.set_h_initial(s0_state.h);
        result.increase_h(s0_state.h);
        return result;
    }

    Node n0 = make_root_node(s0_state);
    open.push_back(n0);
    closed.insert(s0_state.CompressedState);
    result.set_h_initial(n0.state.h);

    vector<tuple<long long, char>> successors = succ(n0, n0.action, puzzle_size);
    for(auto successor: successors) {
        result = run(s0, puzzle_size);
        if(result.get_optimal_length() == -1) {
            result.stop_timer();
            result.set_optimal_lenght(n0.g);
            found = true;
            break;
        }
    }
    result.stop_timer();
    result.set_h_total(-1);
    return result;
};