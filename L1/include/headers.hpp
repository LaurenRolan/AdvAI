#pragma once
#include <vector>
#include <array>
#include <set>
#include <deque>
#include <string>
#include <cstring>


int main(int argc, char* argv[]);

int get_puzzle_size(int argc, char* argv[]);

char* get_algorithm_name(int argc, char* argv[]);

std::vector<std::string> get_s0_entries(int argc, char* argv[], int puzzle_size);

std::string init(std::string state_0);

bool is_goal(std::string state, int n_puzzle);

std::vector<char> succ(std::string state, int n_puzzle, char previous_action);

// Defining BFS stuff aqui por enquanto
typedef struct bfs_node
{
    bfs_node* parent;
    std::string state;
    int g; // custo do caminho

    friend bool operator==(const bfs_node& lhs, const bfs_node& rhs)
    {
        return lhs.state.compare(rhs.state) == 0 and
            lhs.g == rhs.g and
            lhs.parent == rhs.parent;
    }
};

bfs_node make_root_node(std::string s0);

class BFS{
    private:
    std::set<std::string> closed;
    std::deque<bfs_node> open;

    public:
    std::vector<bfs_node> run(std::string s0, int n_puzzle);  
};
