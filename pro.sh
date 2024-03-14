#!/bin/bash

# Input sizes
INPUT_SIZES=(64 128 256 512 1024 2048 4096 8192 16384 32768)

# Number of runs for averaging
NUM_RUNS=10

# Output file
OUTPUT_FILE=output.csv

# Function to run and measure execution time of a program
run_program() {
    local program=$1
    local size=$2
    local time=$( { time -p $program $size $size >/dev/null 2>&1; } 2>&1 )
    echo $time | grep real | awk '{print $2}'
}

# Print header to output file
echo "Size,MPIN,OMPT,ompN,MPIT,seq" > $OUTPUT_FILE

# Loop over input sizes
for size in ${INPUT_SIZES[@]}; do
    echo "Running for size: $size"

    # Initialize variables for averaging
    mpin_sum=0
    ompt_sum=0
    ompn_sum=0
    mpit_sum=0
    seq_sum=0

    # Run each program multiple times and sum the execution times
    for ((i=0; i<$NUM_RUNS; i++)); do
        # Run MPI program (MPIN)
        mpin_time=$(run_program "mpirun -n 4 ./mpi_matrix_vector_multiply" $size)
        mpin_sum=$(echo "$mpin_sum + $mpin_time" | bc)

        # Run OpenMP program (OMPT)
        ompt_time=$(run_program "./openmp_matrix_vector_multiply" $size)
        ompt_sum=$(echo "$ompt_sum + $ompt_time" | bc)

        # Run OpenMP program (ompN)
        ompn_time=$(run_program "./openmp_matrix_vector_multiply_tiled" $size)
        ompn_sum=$(echo "$ompn_sum + $ompn_time" | bc)

        # Run MPI program (MPIT)
        mpit_time=$(run_program "mpirun -n 4 ./MPIT" $size)
        mpit_sum=$(echo "$mpit_sum + $mpit_time" | bc)

        # Run sequential program
        seq_time=$(run_program "./matrix_vector_multiply" $size)
        seq_sum=$(echo "$seq_sum + $seq_time" | bc)
    done

    # Calculate averages
    mpin_avg=$(echo "scale=4; $mpin_sum / $NUM_RUNS" | bc)
    ompt_avg=$(echo "scale=4; $ompt_sum / $NUM_RUNS" | bc)
    ompn_avg=$(echo "scale=4; $ompn_sum / $NUM_RUNS" | bc)
    mpit_avg=$(echo "scale=4; $mpit_sum / $NUM_RUNS" | bc)
    seq_avg=$(echo "scale=4; $seq_sum / $NUM_RUNS" | bc)

    # Print results to output file
    echo "$size,$mpin_avg,$ompt_avg,$ompn_avg,$mpit_avg,$seq_avg" >> $OUTPUT_FILE
done

echo "Output written to $OUTPUT_FILE"
