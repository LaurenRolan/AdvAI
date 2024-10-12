#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
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

vector<array<int, 16>> get_s0_entries(int argc, char* argv[], int puzzle_size)
{
	vector<array<int, 16>> entries;
	array<int, 16> current_entries; 
	int counter = 0;
	for(int i = 2; i < argc; i++)
	{
		int temp;
		sscanf(argv[i], "%d", &temp);
		current_entries[counter] = temp;
		counter++;
		if(counter == puzzle_size)
		{
			counter = 0;
			entries.push_back(current_entries);
		}		
	}
	return entries;
}