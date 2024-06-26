// %%writefile my_code.cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void matrixMulKernel(int *d_matrixA, int *d_matrixB, int *d_matrixC, int rowsA, int colsA, int colsB) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < rowsA && col < colsB) {
        int sum = 0;
        for (int i = 0; i < colsA; i++) {
            sum += d_matrixA[row * colsA + i] * d_matrixB[i * colsB + col];
        }
        d_matrixC[row * colsB + col] = sum;
    }
}

int main() {
    FILE *inputFile = fopen("simba.txt", "r");
    if (!inputFile) {
        printf("Error opening input file.\n");
        return -1;
    }

    char operation[100];
    char dataType[100];
    int matrixADims[2], matrixBDims[2];
    
    fgets(operation, sizeof(operation), inputFile);
    fgets(dataType, sizeof(dataType), inputFile);
    
    fscanf(inputFile, "%dx%d", &matrixADims[0], &matrixADims[1]);
    int rowsA = matrixADims[0], colsA = matrixADims[1];
    
    int *hostMatrixA = (int *)malloc(rowsA * colsA * sizeof(int));
    if (!hostMatrixA) {
        printf("Memory allocation failed for Matrix A.\n");
        return -1;
    }
    
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            fscanf(inputFile, "%d", &hostMatrixA[i * colsA + j]);//host matrixA me phla matrix agya
        }
    }

    fscanf(inputFile, "%dx%d", &matrixBDims[0], &matrixBDims[1]);
    int rowsB = matrixBDims[0], colsB = matrixBDims[1];
    
    int *hostMatrixB = (int *)malloc(rowsB * colsB * sizeof(int));
    if (!hostMatrixB) {
        printf("Memory allocation failed for Matrix B.\n");
        free(hostMatrixA);
        return -1;
    }
    
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            fscanf(inputFile, "%d", &hostMatrixB[i * colsB + j]);//host matrixB me second matrix agya
        }
    }

    fclose(inputFile);

    int *hostMatrixC = (int *)malloc(rowsA * colsB * sizeof(int));
    if (!hostMatrixC) {
        printf("Memory allocation failed for Matrix C.\n");
        free(hostMatrixA);
        free(hostMatrixB);
        return -1;
    }

    int *deviceMatrixA, *deviceMatrixB, *deviceMatrixC;
    cudaMalloc((void **)&deviceMatrixA, rowsA * colsA * sizeof(int));//Tenon matrices ke lia gpu pe memory allocate hogai
    cudaMalloc((void **)&deviceMatrixB, rowsB * colsB * sizeof(int));
    cudaMalloc((void **)&deviceMatrixC, rowsA * colsB * sizeof(int));

    cudaMemcpy(deviceMatrixA, hostMatrixA, rowsA * colsA * sizeof(int), cudaMemcpyHostToDevice);//jo gpu ka matrices tha un me hostmatrix a or b ka data rkhwa dia.
    cudaMemcpy(deviceMatrixB, hostMatrixB, rowsB * colsB * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);  //16 threads x dim ke lia or 16 y ke lia or z ke lia 1
    dim3 numBlocks((colsB + threadsPerBlock.x - 1) / threadsPerBlock.x,
                   (rowsA + threadsPerBlock.y - 1) / threadsPerBlock.y);//grid ki dimension set kr rha jo kernel func exec kre ga
    
    matrixMulKernel<<<numBlocks, threadsPerBlock>>>(deviceMatrixA, deviceMatrixB, deviceMatrixC, rowsA, colsA, colsB);

    cudaMemcpy(hostMatrixC, deviceMatrixC, rowsA * colsB * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(deviceMatrixA);
    cudaFree(deviceMatrixB);
    cudaFree(deviceMatrixC);

    FILE *outputFile = fopen("out.txt", "w");
    if (!outputFile) {
        printf("Error opening output file.\n");
        free(hostMatrixA);
        free(hostMatrixB);
        free(hostMatrixC);
        return -1;
    }

    fprintf(outputFile, "%s", dataType);
    fprintf(outputFile, "%dx%d\n", rowsA, colsB);

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            fprintf(outputFile, "%d ", hostMatrixC[i * colsB + j]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);

    free(hostMatrixA);
    free(hostMatrixB);
    free(hostMatrixC);

    return 0;
}

// !nvcc -o my_code my_code.cu
// !./my_code
