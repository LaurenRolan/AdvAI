#!/bin/bash

input_file="8puzzle_instances.txt"
algorithms=("bfs" "gbfs" "astar" "idastar" "idfs")


# Loop through each algorithm
for algorithm in "${algorithms[@]}"; do
    output_file="${algorithm}_output.txt"
    > "$output_file"
    while IFS= read -r line; do
        ./main -"$algorithm" $line >> "$output_file"
    done < "$input_file"
done

input_file_15="8puzzle_instances.txt"
algorithm="astar"
output_file="${algorithm}_15_output.txt"
> "$output_file"
while IFS= read -r line; do
    ./main -"$algorithm" $line >> "$output_file"
done < "$input_file_15"