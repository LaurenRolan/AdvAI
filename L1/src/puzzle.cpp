#include "../include/puzzle.h"
#include <iostream>

using namespace std;

long long compress_state(deque<char> state, char puzzle_size)
{
    long long compressed = 0;
    char mask = 15; //0F
    // vector: [pos_0, pos_1, ..., pos_X-1, pos_X]
    for(int i = 0; i < puzzle_size; i++)
    {
        char cell = state.front();
        state.pop_front();

        compressed = (compressed | cell);
        if(i != puzzle_size - 1) compressed = compressed << 4;
    }
    return compressed;
}

deque<char> decompress_state(long long state, char puzzle_size)
{
    char checkpoint = puzzle_size == 9 ? 5 : 8;
    char mask_small = 15; //0F
    char mask_byte = 255; //FF

    deque<char> decompressed;

    for(int i = 0; i < checkpoint; i++)
    {
        char last_byte = state & mask_byte;
        state = state >> 8;
        cout << state << "  ";
        char pos_1 = last_byte & mask_small;
        char pos_0 = (last_byte & (mask_small << 4)) >> 4;
        cout << int(pos_0) << " " << int(pos_1) << "\n";
        decompressed.push_front(pos_1);
        if(decompressed.size() < puzzle_size)
            decompressed.push_front(pos_0);
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