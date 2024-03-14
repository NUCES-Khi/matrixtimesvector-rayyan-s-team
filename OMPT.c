

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


#define TILE_SIZE 16 // Size of the tiles

// Function to allocate memory for a matrix
double **allocate_matrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to allocate memory for a vector
double *allocate_vector(int size) {
    double *vector = (double *)malloc(size * sizeof(double));
    if (vector == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return vector;
}

// Function to fill matrix and vector with random values
void fill_random_values(double **matrix, double *vector, int matrix_rows, int matrix_cols, int vector_size) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < matrix_rows; i++) {
        for (int j = 0; j < matrix_cols; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX; // Random value between 0 and 1
        }
    }
    #pragma omp parallel for
    for (int i = 0; i < vector_size; i++) {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

// Function to perform matrix-vector multiplication with tiling
void matrix_vector_multiply(double **matrix, double *vector, double *result, int matrix_rows, int matrix_cols) {
    #pragma omp parallel for
    for (int i = 0; i < matrix_rows; i += TILE_SIZE) {
        for (int j = 0; j < matrix_cols; j++) {
            double sum = 0.0;
            for (int k = i; k < i + TILE_SIZE && k < matrix_rows; k++) {
                sum += matrix[k][j] * vector[k];
            }
            #pragma omp atomic
            result[j] += sum;
        }
    }
}

// Function to free memory allocated for a matrix
void free_matrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to free memory allocated for a vector
void free_vector(double *vector) {
    free(vector);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s matrix_size vector_size\n", argv[0]);
        return EXIT_FAILURE;
    }

    int matrix_rows = atoi(argv[1]);
    int matrix_cols = atoi(argv[1]); // Assuming square matrix
    int vector_size = atoi(argv[2]);

    // Seed the random number generator
    srand(time(NULL));

    // Allocate memory for matrix and vector
    double **matrix = allocate_matrix(matrix_rows, matrix_cols);
    double *vector = allocate_vector(vector_size);
    double *result = allocate_vector(matrix_rows);

    // Fill matrix and vector with random values
    fill_random_values(matrix, vector, matrix_rows, matrix_cols, vector_size);

    // Perform matrix-vector multiplication with tiling
    clock_t start = clock();
    matrix_vector_multiply(matrix, vector, result, matrix_rows, matrix_cols);
    clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by OMP Tiling program : %f seconds\n", time_taken);


    // Free allocated memory
    free_matrix(matrix, matrix_rows);
    free_vector(vector);
    free_vector(result);


    return EXIT_SUCCESS;
}


