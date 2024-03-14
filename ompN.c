#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
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

// Function to perform matrix-vector multiplication
double *matrix_vector_multiply(double **matrix, double *vector, int matrix_rows, int matrix_cols) {
    double *result = allocate_vector(matrix_rows);
    #pragma omp parallel for
    for (int i = 0; i < matrix_rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < matrix_cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
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

    // Fill matrix and vector with random values
    fill_random_values(matrix, vector, matrix_rows, matrix_cols, vector_size);
    
    clock_t start = clock();

    // Perform matrix-vector multiplication
    double *result = matrix_vector_multiply(matrix, vector, matrix_rows, matrix_cols);
    
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by naive OMP: %f seconds\n", time_taken);

    
    // Print the result
   // printf("Result:\n");
   // for (int i = 0; i < matrix_rows; i++) {
  //      printf("%lf\n", result[i]);
//}

    // Free allocated memory
    free_matrix(matrix, matrix_rows);
    free_vector(vector);
    free(result);

    return EXIT_SUCCESS;
}


