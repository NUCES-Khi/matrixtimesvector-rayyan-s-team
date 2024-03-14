#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define MATRIX_SIZE 1000
#define TILE_SIZE 100

void matrixVectorMult(int* matrix, int* vector, int* result, int size, int rows_per_proc) {
    for (int i = 0; i < rows_per_proc; i++) {
        result[i] = 0;
        for (int j = 0; j < size; j++) {
            result[i] += matrix[i * size + j] * vector[j];
        }
    }
}

int main(int argc, char** argv) {
    int rank, num_procs;
    int matrix[MATRIX_SIZE][MATRIX_SIZE], vector[MATRIX_SIZE], result[MATRIX_SIZE];
    int rows_per_proc, remaining_rows;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    rows_per_proc = MATRIX_SIZE / num_procs;
    remaining_rows = MATRIX_SIZE % num_procs;

    if (rank == 0) {
        // Initialize matrix and vector
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = rand() % 10; // Random matrix elements
            }
            vector[i] = rand() % 10; // Random vector elements
        }
    }

    // Broadcast vector to all processes
    MPI_Bcast(vector, MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter matrix rows to different processes
    int* local_matrix = (int*)malloc(sizeof(int) * rows_per_proc * MATRIX_SIZE);
    MPI_Scatter(matrix, rows_per_proc * MATRIX_SIZE, MPI_INT, local_matrix, rows_per_proc * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform matrix-vector multiplication locally
    clock_t start = clock();
    matrixVectorMult(local_matrix, vector, result, MATRIX_SIZE, rows_per_proc);

    // Gather results from all processes
    int* gathered_results = NULL;
    if (rank == 0) {
        gathered_results = (int*)malloc(sizeof(int) * MATRIX_SIZE);
    }
    MPI_Gather(result, rows_per_proc, MPI_INT, gathered_results, rows_per_proc, MPI_INT, 0, MPI_COMM_WORLD);


    free(local_matrix);
    MPI_Finalize();
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by MPI Tiling program : %f seconds\n", time_taken);
    return 0;
}
