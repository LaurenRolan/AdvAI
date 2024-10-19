#include "../include/puzzle.h"
#include <iostream>
#include<math.h>  

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
        char pos_1 = last_byte & mask_small;
        char pos_0 = (last_byte & (mask_small << 4)) >> 4;
        decompressed.push_front(pos_1);
        if(decompressed.size() < puzzle_size)
            decompressed.push_front(pos_0);
    }
    return decompressed;
}

char get_h(State state, char puzzle_size)
{
    deque<char> decompressed = decompress_state(state.CompressedState, puzzle_size);
    char width = puzzle_size == 9 ? 3 : 4;

    char distance = 0;
    for(int i = 0; i < decompressed.size(); i++)
    {
        char val = decompressed[i];
        if(val != 0)
            distance += abs(val % 3 - i % 3) + abs(floor(val / 3) - floor(i / 3));
    }
    return distance;
}

bool is_goal(State state, char puzzle_size)
{
	if(puzzle_size == 16)
	{
		return GOAL_N_15 == state.CompressedState;
	}
	if(puzzle_size == 9)
	{
		return GOAL_N_8 == state.CompressedState;
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