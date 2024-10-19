#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstddef>
#include <deque>
#include <vector>
#include <set>

using namespace std;

void print_state(deque<char> state);

void print_state(deque<char> state)
{
	for(int i = 0; i < state.size(); i++)
	{
		cout << int(state[i]) << " ";
	}
	cout << "\n";
}

int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	Algorithm algorithm = get_algorithm(argc, argv);
	deque<deque<char>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm == Algorithm::NONE)
		return 1;

	cout << "Entries: \n";
	print_state(s0_entries[0]);
	print_state(s0_entries[1]);

	cout << "Compressed: \n";
	long long result1, result2;
	result1 = compress_state(s0_entries[0], puzzle_size);
	cout << result1 << "\n";
	result2 = compress_state(s0_entries[1], puzzle_size);
	cout << result2 << "\n";

	cout << "Decompressed: \n";
	deque<char> state1 = decompress_state(result1, puzzle_size);
	print_state(state1);
	deque<char> state2 = decompress_state(result2, puzzle_size);
	print_state(state2);

	cout << "Manhattan: \n";
	State s1 = {result1, 0};
	State s2 = {result2, 0};
	cout << int(get_h(s1, 9)) << "\n"; 
	cout << int(get_h(s2, 9)) << "\n"; 

	// cout << "s0: " << s0.c_str() << "\n";
	// cout << is_goal(s0, puzzle_size) << "\n";
	// cout << is_goal(init(s0), puzzle_size) << "\n";

	// BFS algo;
	// int path_size = algo.run(s0, puzzle_size);
	// cout << s0 << "   length: " << path_size << "\n";

	return 0;
}
