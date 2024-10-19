#ifndef UTILS_H
#define UTILS_H
#include "../include/puzzle.h"
#include <vector>
#include <array>
#include <set>
#include <deque>
#include <string>
#include <cstring>


int main(int argc, char* argv[]);

// Get the puzzle size (9 or 16)
int get_puzzle_size(int argc, char* argv[]);

// Get the algorithm name (bfs, astar, idastar, etc)
char* get_algorithm_name(int argc, char* argv[]);

// Get a vector of initial states, coded as strings of size puzzle_size
std::vector<std::string> get_s0_entries(int argc, char* argv[], int puzzle_size);



#endif
