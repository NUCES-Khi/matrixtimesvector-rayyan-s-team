#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define MAX_VALUE 10

void generate_random_matrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = rand() % (MAX_VALUE + 1);
        }
    }
}

void generate_random_vector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % (MAX_VALUE + 1);
    }
}

void print_matrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void print_vector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void matrix_vector_multiply(int *matrix, int *vector, int *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, world_size;
    int *matrix, *vector, *result;
    int rows, cols, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc != 3) {
        if (rank == 0) {
            printf("Usage: %s <rows> <cols>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    size = rows;

    if (cols != size || size % world_size != 0) {
        if (rank == 0) {
            printf("Invalid matrix and vector dimensions.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Allocate memory for matrix, vector, and result
    matrix = (int *)malloc(rows * cols * sizeof(int));
    vector = (int *)malloc(cols * sizeof(int));
    result = (int *)malloc(rows * sizeof(int));

    if (rank == 0) {
        // Generate random matrix and vector
        srand(time(NULL));
        generate_random_matrix(matrix, rows, cols);
        generate_random_vector(vector, size);

       // printf("Matrix:\n");
       // print_matrix(matrix, rows, cols);

//printf("\nVector:\n");
       // print_vector(vector, size);
    }

    // Broadcast matrix and vector to all processes
    MPI_Bcast(matrix, rows * cols, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector, cols, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate local portion of result
    int local_rows = rows / world_size;
    int *local_result = (int *)malloc(local_rows * sizeof(int));

    double start_time = MPI_Wtime();

    matrix_vector_multiply(matrix + rank * local_rows * cols, vector, local_result, local_rows, cols);

    double end_time = MPI_Wtime();

    // Gather local results to root process
    MPI_Gather(local_result, local_rows, MPI_INT, result, local_rows, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
       // printf("\nResult:\n");
     //   print_vector(result, rows);

        printf("\nTime taken by Naive MPI: %.6f seconds\n", end_time - start_time);
    }

    // Clean up
    free(matrix);
    free(vector);
    free(result);
    free(local_result);

    MPI_Finalize();
    return 0;
}
