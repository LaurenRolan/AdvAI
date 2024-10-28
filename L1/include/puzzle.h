#ifndef PUZZLE_H
#define PUZZLE_H
// Puzzle-specific utils
#include <cstddef>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>

const long long GOAL_N_15 = 81985529216486895; // 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
const long long GOAL_N_8 = 305419896; // 0001 0010 0011 0100 0101 0110 0111 1000

enum Algorithm
{
    a_BFS,
    a_IDFS,
    a_GBFS,
    a_ASTAR,
    a_IDASTAR,
    a_NONE
};

// State struct
// CompressedState -> 8 bytes indicating the compressed state info
// h -> heuristic value for this state (dist. Manhattan)
struct State
{
    long long CompressedState;
    int h;
};

// Node struct
// state -> state struct
// g -> path cost until this node
// action -> action that took us to this new state
// index -> order of node creation
struct Node
{
    State state;
    int g;
    char action;
    int index;
    short depth;
};

class Result
{
public:
  void start_timer();
  void stop_timer();
  void increase_expanded();
  void increase_generated();
  void set_optimal_lenght(int lenght);
  void print_result();
  void write_result(std::string filename);
  void set_h_initial(int new_h);
  void increase_h(int new_h);
  void set_h_total(int new_h);
  short get_optimal_length();

private:
  int expanded_nodes = 0;
  int generated_nodes = 0;
  int counter = 0;
  short optimal_length;
  float duration;
  double avg_h;
  short initial_h;
  double total_h = 0;
  clock_t start_time;
  std::string printable_result;
  void get_result();
};

#pragma region StateManagement
// Given a vector of chars representing the decompressed state, returns a long long.
long long compress_state(std::deque<char> state, char puzzle_size);

// Given a long long representation of a compressed state, returns a vector of chars.
std::deque<char> decompress_state(long long state, char puzzle_size);

// Calculates the Manhattan distance for a given state
char get_h(std::deque<char> state, char puzzle_size);
#pragma endregion

// Get root node for a given initial state
Node make_root_node(State s0);

// Get node for a given set of <n, a, s'>
Node make_node(int cost, long long state, char action, char puzzle_size, int index);

// Get node for a given set of <n, a, s'> with depth set as well
Node make_node_with_depth(int cost, long long state, char action, char puzzle_size, int index, short depth);

// Get the initial state
State init(std::deque<char> state_0, char puzzle_size);

// Check if the state is a goal state for a given puzzle_size
bool is_goal(State state, char puzzle_size);

// Get the successors <compressed_state, action> for a given node and puzzle_size
std::vector<std::tuple<long long, char>> succ(Node parent, char previous_action, char puzzle_size);

#endif