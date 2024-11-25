#ifndef UTILS_H
#define UTILS_H
#include "../include/puzzle.h"

int main(int argc, char* argv[]);

// Retorna o tamanho do puzzle (9 para o 8-puzzle, 16 para o 15-puzzle)
int get_puzzle_size(int argc, char* argv[]);

// Retorna o nome do algoritmo (astar, bfs, gbfs, idastar, idfs) 
Algorithm get_algorithm(int argc, char* argv[]);

// Retorna uma lista de estados inicial descompactados
std::deque<std::deque<char>> get_s0_entries(int argc, char* argv[], char puzzle_size);

// Imprime um estado, dado sua versão descomprimida.
// Usado apenas para debug.
void print_state(std::deque<char> state);

// Imprime um estado, dado sua versão comprimida.
// Usado apenas para debug.
void print_state(long long state, char puzzle_size);

#endif
