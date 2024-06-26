#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

void call_read_and_calc(const char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    char dimension[256];

    for (int i = 0; i < 2; i++)
    {
        if (fgets(dimension, sizeof(dimension), fp) == NULL)
        {
            perror("Error reading file");
            fclose(fp);
            return;
        }
    }

    if (fgets(dimension, sizeof(dimension), fp) == NULL)
    {
        perror("Error reading file");
        fclose(fp);
        return;
    }

    printf("Dim is: %s\n", dimension);
    int rows = atoi(strtok(dimension, "X"));
    int col = atoi(strtok(NULL, "X"));
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = (int *)malloc(col * sizeof(int));
        if (matrix[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            fclose(fp);
            return;
        }
    }

    char word[50];
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1)
            {
                perror("Error reading matrix element");
                fclose(fp);
                for (int k = 0; k < rows; ++k)
                {
                    free(matrix[k]);
                }
                free(matrix);
                return;
            }

            // Check for the end of line or file
            int nextChar = fgetc(fp);
            if (nextChar == '\n' || nextChar == EOF)
            {
                break;
            }
            // else if (nextChar != ',')
            // {
            //     perror("Error: Invalid matrix format");
            //     fclose(fp);
            //     for (int k = 0; k < rows; ++k)
            //     {
            //         free(matrix[k]);
            //     }
            //     free(matrix);
            //     return;
            // }
        }
    }
    if (fgets(dimension, sizeof(dimension), fp) == NULL)
    {
        printf("FIle ENd /n");
    }

    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        matrix2[i] = (int *)malloc(col * sizeof(int));
        if (matrix2[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(matrix2[j]);
            }
            free(matrix2);
            fclose(fp);
            return;
        }
    }

    // char word[50];
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (fscanf(fp, "%d", &matrix2[i][j]) != 1)
            {
                perror("Error reading matrix element");
                fclose(fp);
                for (int k = 0; k < rows; ++k)
                {
                    free(matrix2[k]);
                }
                free(matrix2);
                return;
            }

            // Check for the end of line or file
            int nextChar = fgetc(fp);
            if (nextChar == '\n' || nextChar == EOF)
            {
                break;
            }
            else if (nextChar != ',')
            {
                perror("Error: Invalid matrix format");
                fclose(fp);
                for (int k = 0; k < rows; ++k)
                {
                    free(matrix2[k]);
                }
                free(matrix2);
                return;
            }
        }
    }

    fclose(fp);

    // Print the matrix
    printf("Matrix:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Matrix2:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    

    int **Result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        Result[i] = (int *)malloc(col * sizeof(int));
        if (Result[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(Result[j]);
            }
            free(Result);
            return;
        }
    }
    // int i, j, k, sum;
    // omp_set_nested(1);
    // omp_set_num_threads(4);

    // #pragma omp parallel for default(none) shared(matrix, matrix2, Result, rows, col, sum) private(i, j)
    // for (i = 0; i < rows; i++) {
    //     #pragma omp parallel for default(none) shared(matrix, matrix2, Result, i, col, rows) private(j, k) reduction(+:sum)
    //     for (j = 0; j < col; j++) {
    //         sum = 0;
    //         for (k = 0; k < rows; k++) {
    //             sum += matrix[i][k] * matrix2[k][j];
    //         }
    //         Result[i][j] = sum;
    //     }
    // }

    int i, j, k;
    omp_set_num_threads(8); // Set the number of threads to 8

    #pragma omp parallel for default(none) shared(matrix, matrix2, Result, rows, col) private(i, j, k)
    for (i = 0; i < rows; i++) {
        for (j = 0; j < col; j++) {
            int sum = 0; // Initialize sum at the start of each iteration
            for (k = 0; k < rows; k++) {
                sum += matrix[i][k] * matrix2[k][j];
            }
            Result[i][j] = sum;
        }
    }

    printf("Result:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d ", Result[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    call_read_and_calc("./inputFIle.txt");
    return 0;
}






    