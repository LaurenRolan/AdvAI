#include "../include/headers.hpp"
using namespace std;

bfs_node make_root_node(string s0)
{
    bfs_node root_node {
        nullptr,
        s0,
        0
    };
    return root_node;
}

// Possible actions:
// u -> move blank up
// d -> move blank down
// l -> move blank left
// r -> move blank right
// n -> none
vector<char> succ(string state, int n_puzzle, char previous_action)
{
    vector<char> possible_actions;
    int width = (n_puzzle % 8 == 0) ? 3 : 4;
    int blank_pos = state.find('0');

    // Se o blank não atingiu a margem direita e previous_action != 'l'
    if((blank_pos + 1) % width != 0 and previous_action != 'l')
    {
        possible_actions.push_back('r');
    }
    // Se o blank não está na margem esquerda e previous_action != 'r'
    if(blank_pos % width != 0 and previous_action != 'r')
    {
        possible_actions.push_back('l');
    }
    // Se o blank não está na linha do topo e previous_action != 'd'
    if(blank_pos >= width and previous_action != 'd')
    {
        possible_actions.push_back('u');
    }
    if((blank_pos <= n_puzzle - width) and previous_action != 'u')
    {
        possible_actions.push_back('d');
    }
    return possible_actions;
}

vector<bfs_node> BFS::run(string s0, int n_puzzle)
{
    vector<bfs_node> path;

    if(is_goal(init(s0), n_puzzle))
    {
        return path;
    }
    open.push_back(make_root_node(s0));
    closed.insert(s0);
    
    while(!open.empty())
    {
        bfs_node n = open.front();
        open.pop_front();

        //foreach succ(n.state)...
    }

}