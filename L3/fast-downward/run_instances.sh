#!/bin/bash

# Definir o diretório correto
directory="../castle"

# Verificar se o diretório existe
if [ ! -d "$directory" ]; then
    echo "Diretório $directory não encontrado!"
    exit 1
fi

# Loop para processar cada arquivo .pddl na pasta ../castle
for problem_file in "$directory"/*.pddl; do
    if [ ! -f "$problem_file" ]; then
        echo "Arquivo não encontrado: $problem_file"
        continue
    fi

    echo "Processando: $problem_file"
    
    # Extrai o nome do arquivo sem o caminho completo
    file_name=$(basename "$problem_file")

    # Executa o Fast Downward com timeout de 5 segundos
    output=$(gtimeout 5 python3 fast-downward.py domain.pddl "$problem_file" --search "astar(lmcut())" 2>&1) ## <<< Definir search aqui

    # Verifica se o processo demorou mais que o tempo limite
    if [[ $? -eq 124 ]]; then
        echo "$file_name: TEMPO EXCEDIDO"
        continue
    fi

    # Extrai o Plan cost da saída usando awk
    plan_cost=$(echo "$output" | awk '/Plan cost:/ {print}')

    # Verifica se conseguiu extrair o custo e imprime
    if [ -n "$plan_cost" ]; then
        echo "$file_name: $plan_cost"
    else
        echo "$file_name: ERRO AO EXTRAIR O CUSTO"
    fi
done
