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

// void print_state(deque<char> state)
// {
// 	for(int i = 0; i < state.size(); i++)
// 	{
// 		cout << int(state[i]) << " ";
// 	}
// 	cout << "\n";
// }

int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	Algorithm algorithm = get_algorithm(argc, argv);
	deque<deque<char>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm == Algorithm::a_NONE)
		return 1;

	for(int i = 0; i < s0_entries.size(); i++)
	{
		BFS algo;
		Result result = algo.run(s0_entries[i], puzzle_size);
		result.print_result();
	}
	
	return 0;
}
