#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../include/puzzle.h"
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

// Class defining the IDA* algorithm
class IDAStar : public SearchAlgorithm {
    public:
    Result run(deque<char> s0, char puzzle_size) override;
    private:
    tuple<int, bool> recursive_search(Node n0, int f_limit, Result& result);
};

struct CompareAStarNode
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        // P0 : min f (= h + g)
        if(lhs.state.h + lhs.g != rhs.state.h + rhs.g)
            return lhs.state.h + lhs.g > rhs.state.h + rhs.g;
        // P1 : min h 
        if(lhs.state.h != rhs.state.h)
            return lhs.state.h > rhs.state.h;
        //P2 : max index (LIFO)
        return lhs.index < rhs.index;
    }
};

struct CompareGBFSNode
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        // P0: min f (=h)
        if(lhs.state.h != rhs.state.h)
            return  lhs.state.h > rhs.state.h;
        // P1: max g
        if(lhs.g != rhs.g)
            return lhs.g < rhs.g;
        // P2: max index (LIFO)
        return lhs.index < rhs.index;
    }
};


#endif