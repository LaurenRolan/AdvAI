#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include "../include/headers.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	int puzzle_size = get_puzzle_size(argc, argv);
	char* algorithm_name = get_algorithm_name(argc, argv);
	vector<array<int, 16>> s0_entries = get_s0_entries(argc, argv, puzzle_size);

	if(puzzle_size == -1 || algorithm_name == nullptr)
		return 1;

	cout << "Valid entries!";
	return 0;
}
