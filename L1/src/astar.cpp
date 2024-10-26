#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

Result AStar::run(deque<char> s0, char puzzle_size)
{
    Result result;
    unordered_set<long long> closed;
    priority_queue<Node, vector<Node>, CompareAStarNode> open;
    int index = 0;
    
    result.start_timer();
    State s0_state = init(s0, puzzle_size);
    Node n0 = make_root_node(s0_state);
    open.push(n0);
    result.set_h_initial(n0.state.h);
    result.increase_h(n0.state.h);

    while(!open.empty())
    {
        Node n = open.top();
        open.pop();

        if(closed.find(n.state.CompressedState) == closed.end())
        {
            closed.insert(closed.begin(), n.state.CompressedState);
            if(is_goal(n.state, puzzle_size))
            {
                result.stop_timer();
                result.set_optimal_lenght(n.g);
                return result;
            }
            result.increase_expanded();

            vector<tuple<long long, char>> successors = succ(n, n.action, puzzle_size);
            for(auto successor: successors)
            {
                long long state = get<0>(successor);
                char action = get<1>(successor);
                
                Node n_line = make_node(n.g, state, action, puzzle_size, ++index);
                result.increase_generated();
                result.increase_h(n_line.state.h);
                open.push(n_line);
            };
        }
    }
    result.stop_timer();
    result.set_h_total(-1);
    return result;
}