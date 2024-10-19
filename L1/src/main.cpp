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

int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	Algorithm algorithm = get_algorithm(argc, argv);
	deque<deque<char>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm == Algorithm::NONE)
		return 1;

	// cout << "s0: " << s0.c_str() << "\n";
	// cout << is_goal(s0, puzzle_size) << "\n";
	// cout << is_goal(init(s0), puzzle_size) << "\n";

	// BFS algo;
	// int path_size = algo.run(s0, puzzle_size);
	// cout << s0 << "   length: " << path_size << "\n";

	return 0;
}
