#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../include/puzzle.h"
#include <set>
using namespace std;

// Class defining the BFS-Graph algorithm and variables
class BFS{
    public:
    Result run(deque<char> s0, char puzzle_size);
};

#endif