#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <set>
#include "../include/headers.hpp"

using namespace std;

int get_puzzle_size(int argc, char* argv[])
{
	int n_entries = argc - 2;
	int puzzle_size = 0;
	if(n_entries % 9 == 0)
	{
		return 9;
	}
	
	if (n_entries % 16 == 0)
	{
		return 16;
	}

	cout << "\nInvalid number of state entries. Should be a multiple of 8 or 15.\n";
	cout << argc;
	return -1;
}

char* get_algorithm_name(int argc, char* argv[])
{
	set<string> valid_algorithms = {"-bfs", "-idfs", "-astar", "-idastar", "-gbfs"};
	if (valid_algorithms.find(argv[1]) == valid_algorithms.end())
	{
		cout << "\nInvalid algorithm. Use -bfs, -idfs, -astar, -idastar or -gbfs.";
		return nullptr;
	}

	char* algorithm = argv[1] + 1;
	return algorithm;
}

vector<string> get_s0_entries(int argc, char* argv[], int puzzle_size)
{
	vector<string> entries;
	stringstream argv_string;
	argv_string  << argv + 2;
	string current_entries;

	while(getline(argv_string, current_entries, ','))
	{
		entries.push_back(current_entries);
	}
	return entries;
}

string init(string state_0)
{
	return state_0;
}

bool is_goal(string state, int n_puzzle)
{
	string goal_n_15 = "0123456789ABCDEF";
	string goal_n_8 = "012345678";
	if(n_puzzle == 15)
	{
		return goal_n_15.compare(state) == 0;
	}
	if(n_puzzle == 8)
	{
		return goal_n_8.compare(state) == 0;
	}
}