#ifndef PUZZLE_H
#define PUZZLE_H
// Puzzle-specific utils
#include <cstddef>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <chrono>

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
// CompressedState -> 8 bytes que indicam a informação comprimida do estado
// h -> valor da heurística para este estado (dist. Manhattan)
struct State
{
    long long CompressedState;
    int h;
};

// Node struct
// state -> state struct
// g -> custo do caminho até este nodo
// action -> ação que nos trouxe a este nodo
// index -> ordem de criação do nodo
struct Node
{
    State state;
    int g;
    char action;
    int index;
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
  std::chrono::time_point<std::chrono::system_clock> start_time;
  std::string printable_result;
  void get_result();
};

#pragma region StateManagement
// Dado um estado descomprimido, retorna a versão comprimida.
// state -> lista de tamanho N indicando a posição de cada célula no grid
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: long long com o estado comprimido
long long compress_state(std::deque<char> state, char puzzle_size);

// Dado um estado comprimido, retorna a versão descomprimida.
// state -> long long com a versão comprimida do estado
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: deque<char> com o estado descomprimido
std::deque<char> decompress_state(long long state, char puzzle_size);

// Calcula a distância de Manhattan para um dado estado
// state -> lista de tamanho N indicando a posição de cada célula no grid
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: char com o valor da distância
char get_h(std::deque<char> state, char puzzle_size);
#pragma endregion

// Cria o nodo raiz, dado um estado inicial
// s0 -> struct do tipo State, representando o estado inicial
// Returns: struct Node
Node make_root_node(State s0);

// Cria um nodo dado o pai, ação que levou até este nodo, e o estado deste nodo.
// cost -> parent.g, custo do pai
// state -> versão comprimida do estado do nodo
// action -> ação que levou a este nodo
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// index -> ordem de criação do nodo
// Returns: struct Node
Node make_node(int cost, long long state, char action, char puzzle_size, int index);

// Retorna o estado inicial
// state_0 - > versão descomprimida do estado inicial
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: struct State
State init(std::deque<char> state_0, char puzzle_size);

// Verifica se o estado é objetivo, dado o tamanho do puzzle
// state -> struct State com o estado atual
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: True se é objetivo, False caso contrário
bool is_goal(State state, char puzzle_size);

// Gera os sucessores de um estado dado o nodo atual e o tamanho do puzzle, evitando gerar o próprio pai
// parent -> nodo pai
// previous_action -> ação anterior ('u', 'd', 'l', 'r')
// puzzle_size -> tamanho do puzzle atual (9 para o 8-puzzle, 16 para o 15-puzzle)
// Returns: tupla com o próximo estado e ação que levou a ele
std::vector<std::tuple<long long, char>> succ(Node parent, char previous_action, char puzzle_size);

#endif