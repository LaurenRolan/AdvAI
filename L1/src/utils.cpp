// Implementação dos métodos de leitura e parsing da entrada
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <set>
#include "../include/utils.h"

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

	cout << "\nInvalid number of state entries. Should be a multiple of 9 or 16.\n";
	cout << argc;
	return -1;
}

Algorithm get_algorithm(int argc, char* argv[])
{
	set<string> valid_algorithms = {"-bfs", "-idfs", "-astar", "-idastar", "-gbfs"};
	if (valid_algorithms.find(argv[1]) == valid_algorithms.end())
	{
		cout << "\nInvalid algorithm. Use -bfs, -idfs, -astar, -idastar or -gbfs.";
		return Algorithm::a_NONE;
	}

	string algorithm = string(argv[1] + 1);
	if(algorithm == "bfs") return Algorithm::a_BFS;
	if(algorithm == "astar") return Algorithm::a_ASTAR;
	if(algorithm == "idastar") return Algorithm::a_IDASTAR;
	if(algorithm == "idfs") return Algorithm::a_IDFS;
	if(algorithm == "gbfs") return Algorithm::a_GBFS;
	return Algorithm::a_NONE;
}

deque<deque<char>> get_s0_entries(int argc, char* argv[], char puzzle_size)
{
	deque<deque<char>> entries;
	deque<char> line;

	char counter = puzzle_size;
    for (int i = 2; i < argc; ++i) {
        stringstream ss(argv[i]);
        int num;

		if (ss.peek() == ' ' or ss.peek() == ',') {
			ss.ignore(); // Ignore the comma separator
		}
		ss >> num;
		line.push_back(static_cast<char>(num));
		counter--;
		if(counter == 0)
		{
	        entries.push_back(line);
			counter = puzzle_size;
			line.clear();
		}
    }
	return entries;
}
