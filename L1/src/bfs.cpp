#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
using namespace std;

// bfs_node make_node(bfs_node* parent, char action, int puzzle_size)
// {
//     int width = puzzle_size == 9 ? 3 : 4;
//     string current_state = parent->state;

//     // Since action is possible, we just swap the right chars
//     int blank_pos = current_state.find('0');
//     string new_state = current_state;
//     char swap_char = 'n';

//     switch(action)
//     {
//         case 'u':
//             swap_char = current_state[blank_pos - width];
//             new_state[blank_pos - width] = '0';
//             new_state[blank_pos] = swap_char;
//             break;
//         case 'd':
//             swap_char = current_state[blank_pos + width];
//             new_state[blank_pos + width] = '0';
//             new_state[blank_pos] = swap_char;
//             break;
//         case 'l':
//             swap_char = current_state[blank_pos - 1];
//             new_state[blank_pos - 1] = '0';
//             new_state[blank_pos] = swap_char;
//             break;
//         case 'r':
//             swap_char = current_state[blank_pos + 1];
//             new_state[blank_pos + 1] = '0';
//             new_state[blank_pos] = swap_char;
//             break;
//     }
//     return bfs_node {parent, new_state, parent->g + 1};
// }


int BFS::run(deque<char> s0, char puzzle_size)
{
    State s0_compressed = init(s0, puzzle_size);
    if(is_goal(s0_compressed, puzzle_size))
    {
        return 0;
    }
    open.push_back(make_root_node(s0_compressed));
    closed.insert(s0_compressed);
    
    while(!open.empty())
    {
        Node n = open.front();
        open.pop_front();

        vector<char> successors = succ(n.state, puzzle_size, n.action);
        while(!successors.empty())
        {
            char action = successors.back();
            successors.pop_back();
            Node n_line = make_node(&n, action, puzzle_size);

            if(is_goal(n_line.state, puzzle_size))
            {
                return 0;//extract path
            }

            if(closed.find(n_line.state) == closed.end())
            {
                closed.insert(n_line.state);
                open.push_back(n_line);
            }
        };
    }
    return -1;
}