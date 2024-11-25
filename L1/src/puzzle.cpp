// Implementação dos métodos específicos ao puzzle

#include "../include/puzzle.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

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

char get_h(deque<char> state, char puzzle_size)
{
    char width = puzzle_size == 9 ? 3 : 4;

    char distance = 0;
    for(int i = 0; i < state.size(); i++)
    {
        char val = state[i];
        if(val != 0)
            distance += abs(val % width - i % width) + abs(floor(val / width) - floor(i / width));
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
        'n',
        0
    };
}

State init(deque<char> s0, char puzzle_size)
{
    long long compressed = compress_state(s0, puzzle_size);
    return State
    {
        compressed,
        get_h(s0, puzzle_size)
    };
}

void print_state(deque<char> state)
{
	for(int i = 0; i < state.size(); i++)
	{
		cout << int(state[i]) << " ";
	}
	cout << "\n";
}

void print_state(long long state, char puzzle_size)
{
	print_state(decompress_state(state, puzzle_size));
}

int get_index(deque<char> state, char target)
{
    auto it = find(state.begin(), state.end(), target);
    if (it != state.end()) {
        return distance(state.begin(), it);
    } else {
        print_state(state);
        std::cout << "target not found in the deque." << std::endl;
    }
    return -1;
}

deque<char> swap(deque<char> state, int index1, int index2)
{
    deque<char> new_state = state;
    char temp = new_state[index1];
    new_state[index1] = new_state[index2];
    new_state[index2] = temp;
    return new_state;
}


// Get node for a given set of <s, s', a>
// Since s' can be derived from <s, a>, only those are passed.
Node make_node(int cost, long long state, char action, char puzzle_size, int index)
{
    State s_line = {
        state,
        get_h(decompress_state(state, puzzle_size), puzzle_size)
    };

    Node node = {
        s_line,
        cost + 1,
        action,
        index,
    };
    return node;
}


// Possible actions:
// u -> move blank up
// d -> move blank down
// l -> move blank left
// r -> move blank right
// n -> none
vector<tuple<long long, char>> succ(Node parent, char previous_action, char puzzle_size)
{
    deque<char> decompressed = decompress_state(parent.state.CompressedState, puzzle_size);
    int width = (puzzle_size == 9) ? 3 : 4;

    vector<tuple<long long, char>> successors;
    int blank_index = get_index(decompressed, 0);
    int swap_index;

    // Se o blank não está na linha do topo e previous_action != 'd'
    if(blank_index >= width and previous_action != 'd')
    {
        swap_index = blank_index - width;
        long long compressed = compress_state(swap(decompressed, blank_index, swap_index), puzzle_size);
        successors.push_back(make_tuple(compressed, 'u'));
    }
    // Se o blank não está na margem esquerda e previous_action != 'r'
    if(blank_index % width != 0 and previous_action != 'r')
    {
        swap_index = blank_index - 1;
        long long compressed = compress_state(swap(decompressed, blank_index, swap_index), puzzle_size);
        successors.push_back(make_tuple(compressed, 'l'));
    }
    // Se o blank não atingiu a margem direita e previous_action != 'l'
    if((blank_index + 1) % width != 0 and previous_action != 'l')
    {
        swap_index = blank_index + 1;
        long long compressed = compress_state(swap(decompressed, blank_index, swap_index), puzzle_size);
        successors.push_back(make_tuple(compressed, 'r'));
    }
    // Se o blank não está na última linha e previous_action != 'u'
    if((blank_index < (puzzle_size - width)) and previous_action != 'u')
    {
        swap_index = blank_index + width;
        long long compressed = compress_state(swap(decompressed, blank_index, swap_index), puzzle_size);
        successors.push_back(make_tuple(compressed, 'd'));
    }

    return successors;
}

#pragma region ResultManagement
void Result::start_timer() { start_time = chrono::high_resolution_clock::now(); }
void Result::stop_timer() { duration = chrono::duration_cast<chrono::duration<float>>(chrono::high_resolution_clock::now() - start_time).count(); }
void Result::increase_expanded() { expanded_nodes++; }
void Result::increase_generated() { generated_nodes++; }
void Result::set_optimal_lenght(int lenght) { optimal_length = lenght; }

void Result::get_result()
{
    if(optimal_length == -1)
    {
        printable_result = "-\n";
        return;
    }
    
    avg_h = total_h/max(counter, 1);
    string res = "";
    res += to_string(expanded_nodes) + ",";
    res += to_string(optimal_length) + ",";
    res += to_string(duration) + ",";
    res += to_string(avg_h) + ",";
    res += to_string(initial_h) + "\n";
    printable_result = res;
}

void Result::print_result()
{
    get_result();
    cout << printable_result;
}

void Result::write_result(std::string filename)
{
    get_result();
    ofstream out_file;
    out_file.open(filename, std::ios_base::app);
    out_file << printable_result;
    out_file.close();
}

void Result::set_h_initial(int new_h) { initial_h = new_h; }
void Result::increase_h(int new_h) { total_h += new_h; counter++; }
void Result::set_h_total(int new_h) { total_h = new_h; }
short Result::get_optimal_length() { return optimal_length; }
#pragma endregion
