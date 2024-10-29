#include "../include/utils.h"
#include "../include/puzzle.h"
#include "../include/algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstddef>
#include <deque>
#include <memory>
#include <vector>
#include <set>

using namespace std;


int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	Algorithm algorithm = get_algorithm(argc, argv);
	deque<deque<char>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm == Algorithm::a_NONE)
		return 1;

	std::unique_ptr<SearchAlgorithm> algo;
	switch(algorithm)
	{
		case a_BFS:
			algo  = std::make_unique<BFS>();
			break;
		case a_GBFS:
			algo  = std::make_unique<GBFS>();
			break;
		case a_ASTAR:
			algo  = std::make_unique<AStar>();
			break;
		case a_IDASTAR:
			algo  = std::make_unique<IDAStar>();
			break;
		case a_IDFS:
			algo  = std::make_unique<IDFS>();
			cout << "IDFS\n";
			break;
		default:
			cout << "None\n";
			return -1;
	}

	for(int i = 0; i < s0_entries.size(); i++)
	{
		Result result = algo->run(s0_entries[i], puzzle_size);
		result.print_result();
	}
	
	return 0;
}
