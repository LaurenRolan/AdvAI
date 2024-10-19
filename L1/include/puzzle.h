#ifndef PUZZLE_H
#define PUZZLE_H
// Puzzle-specific utils
#include <cstddef>
#include <deque>
#include <vector>

// State struct
// CompressedState -> 8 bytes indicating the compressed state info
// h -> heuristic value for this state (dist. Manhattan)
struct State
{
    long long CompressedState;
    std::byte h;

    friend bool operator==(const State& lhs, const State& rhs)
    {
        return lhs.CompressedState == rhs.CompressedState;
    }
};

// Node struct
// state -> state struct
// g -> path cost until this node
// action -> action that took us to this new state
struct Node
{
    State state;
    int g;
    char action;

    friend bool operator==(const Node& lhs, const Node& rhs)
    {
        return lhs.state == rhs.state and
            lhs.g == rhs.g and
            lhs.action == rhs.action;
    }
};

// Given a vector of chars representing the decompressed state, returns a long long.
long long compress_state(std::deque<char> state, char puzzle_size);

// Given a long long representation of a compressed state, returns a vector of chars.
std::deque<char> decompress_state(long long state, char puzzle_size);

// Get root node for a given initial state
Node make_root_node(State s0);

// Get node for a given set of <s, s', a>
// Since s' can be derived from <s, a>, only those are passed.
Node make_node(Node* parent, char action, char puzzle_size);


// Get the initial state
State init(std::deque<char> state_0);

// Check if the state is a goal state for a given puzzle_size
bool is_goal(State state, int puzzle_size);

// Get the successors for a given state and puzzle_size
std::vector<char> succ(State state, int puzzle_size, char previous_action);

#endif