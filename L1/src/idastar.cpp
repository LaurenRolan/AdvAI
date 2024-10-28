#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
#include <iostream>
#include <queue>
#include <limits>
#include <unordered_set>
using namespace std;

const int INFINITY = numeric_limits<int>::max();

Result IDAStar::run(deque<char> s0, char puzzle_size)
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

    int f_limit = n0.state.h;

    while(f_limit < INFINITY)
    {
        cout << ++index << endl;
        tuple<int, bool> search_result = recursive_search(n0, f_limit, result);
        if(get<1>(search_result))
        {
            result.stop_timer();
            return result;
        }
        result.print_result();
        f_limit = get<0>(search_result);
    }
    result.stop_timer();
    result.set_h_total(-1);
    return result;
}

tuple<int, bool> IDAStar::recursive_search(Node n0, int f_limit, Result& result)
{
    int f = n0.g + n0.state.h;
    if(f > f_limit)
        return tuple<int, bool>(f, false);
    if(is_goal(n0.state, 9))
    {
        result.set_optimal_lenght(n0.g);
        return tuple<int, bool>(f, true);
    }

    result.increase_expanded();

    int next_limit = INFINITY;
    auto successors = succ(n0, n0.action, 9);
    for(auto successor: successors)
    {
        long long state = get<0>(successor);
        char action = get<1>(successor);
        Node n_line = make_node(n0.g, state, action, 9, 0);

        cout << "action: " << action << ", h: " << n_line.state.h << endl;

        result.increase_generated();
        result.increase_h(n_line.state.h);

        tuple<int, bool> search_result = recursive_search(n_line, f_limit, result);
        if(get<1>(search_result))
            return search_result;
        next_limit = min(next_limit, get<0>(search_result));
    }
    return tuple<int,bool>(next_limit, false);
}