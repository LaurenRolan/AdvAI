# Set the input file and algorithms array
$input_file = "8puzzle_instances.txt"
$algorithms = @("bfs", "gbfs", "astar", "idastar", "idfs")

# Loop through each algorithm
foreach ($algorithm in $algorithms) {
    $output_file = "${algorithm}_output.txt"
    # Clear the output file if it exists
    Clear-Content -Path $output_file -ErrorAction SilentlyContinue
    
    # Read each line from the input file and run the command
    Get-Content $input_file | ForEach-Object {
        $line = $_.Trim() -split ' '   # Split each line into individual arguments
        & ./main -$algorithm @line | Out-File -Append -FilePath $output_file
    }
}

# Additional section for the specific case
$input_file_15 = "8puzzle_instances.txt"
$algorithm = "astar"
$output_file = "${algorithm}_15_output.txt"
Clear-Content -Path $output_file -ErrorAction SilentlyContinue

Get-Content $input_file_15 | ForEach-Object {
    $line = $_.Trim() -split ' '
    & ./main -$algorithm $line | Out-File -Append -FilePath $output_file
}