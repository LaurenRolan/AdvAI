#pragma once
#include <vector>
#include <array>
#include <set>


int main(int argc, char* argv[]);

int get_puzzle_size(int argc, char* argv[]);

char* get_algorithm_name(int argc, char* argv[]);

std::vector<std::array<int, 16>> get_s0_entries(int argc, char* argv[], int puzzle_size);