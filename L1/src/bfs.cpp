#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
#include <iostream>
#include <unordered_set>
using namespace std;

Result BFS::run(deque<char> s0, char puzzle_size)
{
    Result result;
    unordered_set<long long> closed;
    deque<Node> open;
    
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

    while(!open.empty())
    {
        Node n = open.front();
        open.pop_front();
        result.increase_expanded();

        vector<tuple<long long, char>> successors = succ(n, n.action, puzzle_size);
        for(auto successor: successors)
        {
            long long state = get<0>(successor);
            char action = get<1>(successor);
            
            Node n_line = make_node(n.g, state, action, puzzle_size, 0);
            result.increase_generated();

            if(is_goal(n_line.state, puzzle_size))
            {
                result.stop_timer();
                result.set_optimal_lenght(n_line.g);
                return result;
            }

            if(closed.find(n_line.state.CompressedState) == closed.end())
            {
                closed.insert(n_line.state.CompressedState);
                open.push_back(n_line);
            }
        };
    }
    result.stop_timer();
    result.set_h_total(-1);
    return result;
}