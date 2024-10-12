#include "../include/headers.hpp"

struct bfs_node
{
    int state; // To be defined, precisa ser como uma "hash" do estado
    int h; // heuristica
    int g; // custo do caminho

    // Implementar comparações entre estados
};


class BFS{
    private:
    std::set<bfs_node> closed;
    std::vector<bfs_node> open;

    // Implementar algoritmo
};
