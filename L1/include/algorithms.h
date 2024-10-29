#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../include/puzzle.h"
#include "set"
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

// Class defining the A* algorithm
class AStar : public SearchAlgorithm {
    public:
    Result run(deque<char> s0, char puzzle_size) override;
};

// Class defining the IDFS algorithm
class IDFS : public SearchAlgorithm {
    public:
    Result run(deque<char> s0, char puzzle_size) override;
    
    private:
    bool depth_limited_search(Node n, char puzzle_size, char max_depth, Result &result);
};

#endif