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
    return decompressed;
}

bool is_goal(State state, char puzzle_size)
{
	if(puzzle_size == 16)
	{
    	long long goal_n_16 = 81985529216486895; // 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
		return goal_n_16 == state.CompressedState;
	}
	if(puzzle_size == 9)
	{
        long long goal_n_9 = 305419896; // 0001 0010 0011 0100 0101 0110 0111 1000
		return goal_n_9 == state.CompressedState;
	}
    return false;
}

// Get root node for a given initial state
Node make_root_node(State s0)
{
    return Node {
        s0,
        0,
        'n'
    };
}

State init(deque<char> s0, char puzzle_size)
{
    long long compressed = compress_state(s0, puzzle_size);
    return State
    {
        compressed,
        1, //TODO: Manhattan distance of s_0
    };
}


State next_state(State s, char action, char puzzle_size)
{
    //TODO
    return State {
        0,
        0
    };
}


// Get node for a given set of <s, s', a>
// Since s' can be derived from <s, a>, only those are passed.
Node make_node(Node* parent, char action, char puzzle_size)
{
    State next = next_state(parent->state, action, puzzle_size);
    return Node {
        next,
        parent->g + 1,
        action
    };
}

// Possible actions:
// u -> move blank up
// d -> move blank down
// l -> move blank left
// r -> move blank right
// n -> none
vector<char> succ(State state, char previous_action, char puzzle_size)
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
    vector<char> result;
    result.push_back('n');
    return result;
}