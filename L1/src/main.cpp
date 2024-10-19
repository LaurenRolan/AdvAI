#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../include/headers.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	char* algorithm_name = get_algorithm_name(argc, argv);
	vector<string> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm_name == nullptr)
		return 1;

	cout << "test bfs\n";

	string s0 = s0_entries.back();

	cout << "s0: " << s0.c_str() << "\n";
	cout << is_goal(s0, puzzle_size) << "\n";
	cout << is_goal(init(s0), puzzle_size) << "\n";

	BFS algo;
	int path_size = algo.run(s0, puzzle_size);
	cout << s0 << "   length: " << path_size << "\n";

	return 0;
}
