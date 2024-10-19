#include "../include/puzzle.h"

using namespace std;

long long compress_state(deque<char> state, char puzzle_size)
{
    long long compressed = 0;
    char mask = 15; //0F
    // vector: [byte_0, byte_1, ..., byte_X-1, byte_X]
    for(int i = 0; i < state.size(); i++)
    {
        char two_cells = state.front();
        state.pop_front();

        if(puzzle_size == 16)
        {
            compressed = (compressed | two_cells) << 8;
            continue;
        }

        char cell_0 = two_cells & mask;
        char cell_1 = two_cells & (mask << 4);

        if(cell_0 == 15) //0F
        {
            compressed = (compressed | cell_0) << 4;
            continue;
        }
        if(cell_1 == 15) //0F
        {
            compressed = (compressed | cell_1) << 4;
            continue;   
        }
        compressed = (compressed | two_cells) << 8;
    }
    return compressed;
}

deque<char> decompress_state(long long state, char puzzle_size)
{
    char checkpoint = puzzle_size == 9 ? 2 : 1;
    char mask_small = 15; //0F
    char mask_byte = 255; //FF
    char n_bytes = puzzle_size == 9 ? 6 : 8;

    deque<char> decompressed;

    for(int i = 0; i < n_bytes; i++)
    {
        char back = state & mask_byte;
        state = state >> 8;
        if(i % checkpoint == 0)
        {
            decompressed.push_back(back);
        }
        else
        {
            //TODO
        }
    }
}

// Get root node for a given initial state
Node make_root_node(State s0)
{

}


// bfs_node make_root_node(string s0)
// {
//     bfs_node root_node {
//         nullptr,
//         s0,
//         0,
//         'n'
//     };
//     return root_node;
// }

// Get node for a given set of <s, s', a>
// Since s' can be derived from <s, a>, only those are passed.
Node make_node(Node* parent, char action, int puzzle_size){

}

// Possible actions:
// u -> move blank up
// d -> move blank down
// l -> move blank left
// r -> move blank right
// n -> none
deque<char> succ(Node n, int puzzle_size)
{
    // string state = n.state;
    // char previous_action = n.action;
    // vector<char> possible_actions;
    // int width = (puzzle_size == 9) ? 3 : 4;
    // int blank_pos = state.find('0');

    // if((blank_pos <= puzzle_size - width) and previous_action != 'u')
    // {
    //     possible_actions.push_back('d');
    // }
    // // Se o blank não atingiu a margem direita e previous_action != 'l'
    // if((blank_pos + 1) % width != 0 and previous_action != 'l')
    // {
    //     possible_actions.push_back('r');
    // }
    // // Se o blank não está na margem esquerda e previous_action != 'r'
    // if(blank_pos % width != 0 and previous_action != 'r')
    // {
    //     possible_actions.push_back('l');
    // }
    // // Se o blank não está na linha do topo e previous_action != 'd'
    // if(blank_pos >= width and previous_action != 'd')
    // {
    //     possible_actions.push_back('u');
    // }
    
    // return possible_actions;
}