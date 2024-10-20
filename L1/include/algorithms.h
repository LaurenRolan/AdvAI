#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../include/puzzle.h"
#include <set>
using namespace std;

// Abstract class
class SearchAlgorithm {
    public:
    virtual ~SearchAlgorithm() {}
    virtual Result run(deque<char> s0, char puzzle_size) = 0;
};

// Class defining the BFS-Graph algorithm
class BFS : public SearchAlgorithm {
    public:
    Result run(deque<char> s0, char puzzle_size) override;
};

// Class defining the Greedy Best Fit Search algorithm
class GBFS : public SearchAlgorithm {
    public:
    Result run(deque<char> s0, char puzzle_size) override;
};

#endif