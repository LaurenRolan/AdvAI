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
	char* algorithm_name = get_algorithm_name(argc, argv);
	deque<deque<char>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm_name == nullptr)
		return 1;

	cout << "test bfs\n";
	// Example: print the parsed lines
    for (size_t i = 0; i < s0_entries.size(); ++i) {
        std::cout << "line" << i + 1 << " = [";
        for (size_t j = 0; j < s0_entries[i].size(); ++j) {
            std::cout << static_cast<int>(s0_entries[i][j]);
            if (j < s0_entries[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

	deque<char> s0 = s0_entries.back();

	// cout << "s0: " << s0.c_str() << "\n";
	// cout << is_goal(s0, puzzle_size) << "\n";
	// cout << is_goal(init(s0), puzzle_size) << "\n";

	// BFS algo;
	// int path_size = algo.run(s0, puzzle_size);
	// cout << s0 << "   length: " << path_size << "\n";

	return 0;
}
