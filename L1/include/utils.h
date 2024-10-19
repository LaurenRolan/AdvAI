#ifndef UTILS_H
#define UTILS_H
#include "../include/puzzle.h"

int main(int argc, char* argv[]);

// Get the puzzle size (9 or 16)
int get_puzzle_size(int argc, char* argv[]);

// Get the algorithm name (bfs, astar, idastar, etc)
char* get_algorithm_name(int argc, char* argv[]);

// Get a list of initial states, coded as char lists of size puzzle_size
std::deque<std::deque<char>> get_s0_entries(int argc, char* argv[], char puzzle_size);

#endif
