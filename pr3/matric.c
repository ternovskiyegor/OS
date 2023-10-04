#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix createMatrix(int rows, int cols);
void freeMatrix(Matrix matrix);
void setNewSize(Matrix *matrix, int newRows, int newCols);
void setElement(Matrix *matrix, int row, int col, double value);
double getElement(const Matrix *matrix, int row, int col);
void printMatrix(const Matrix *matrix);
void saveMatrixToFile(const Matrix *matrix, const char *filename);
Matrix readMatrixFromFile(const char *filename);
Matrix addMatrices(const Matrix *matrix1, const Matrix *matrix2);
Matrix subtractMatrices(const Matrix *matrix1, const Matrix *matrix2);
Matrix multiplyMatrixByScalar(const Matrix *matrix, double scalar);
Matrix multiplyMatrices(const Matrix *matrix1, const Matrix *matrix2);

int main() {
    Matrix matrix1 = createMatrix(4, 4);
    Matrix matrix2 = createMatrix(4, 4);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            setElement(&matrix1, i, j, i * 3 + j + 1);
            setElement(&matrix2, i, j, (i * 3 + j + 1) * 10);
        }
    }

    printf("Matrix 1:\n");
    printMatrix(&matrix1);

    printf("Matrix 2:\n");
    printMatrix(&matrix2);

    Matrix sum = addMatrices(&matrix1, &matrix2);
    printf("Sum of matrices:\n");
    printMatrix(&sum);

    Matrix difference = subtractMatrices(&matrix1, &matrix2);
    printf("Difference of matrices:\n");
    printMatrix(&difference);

    Matrix scalarProduct = multiplyMatrixByScalar(&matrix1, 2.0);
    printf("Matrix 1 multiplied by 2:\n");
    printMatrix(&scalarProduct);

    Matrix product = multiplyMatrices(&matrix1, &matrix2);
    printf("Product of matrices:\n");
    printMatrix(&product);

    saveMatrixToFile(&matrix1, "matrix.txt");
    Matrix loadedMatrix = readMatrixFromFile("matrix.txt");
    printf("Matrix ​​read from the file:\n");
    printMatrix(&loadedMatrix);

    freeMatrix(matrix1);
    freeMatrix(matrix2);
    freeMatrix(sum);
    freeMatrix(difference);
    freeMatrix(scalarProduct);
    freeMatrix(product);
    freeMatrix(loadedMatrix);

    return 0;
}

Matrix createMatrix(int rows, int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;

    matrix.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = (double *)malloc(cols * sizeof(double));
    }

    return matrix;
}

void freeMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}

void setNewSize(Matrix *matrix, int newRows, int newCols) {
    Matrix newMatrix = createMatrix(newRows, newCols);
    int minRows = (matrix->rows < newRows) ? matrix->rows : newRows;
    int minCols = (matrix->cols < newCols) ? matrix->cols : newCols;

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minCols; j++) {
            newMatrix.data[i][j] = matrix->data[i][j];
        }
    }
    freeMatrix(*matrix);
    *matrix = newMatrix;
}

void setElement(Matrix *matrix, int row, int col, double value) {
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        matrix->data[row][col] = value;
    }
}

double getElement(const Matrix *matrix, int row, int col) {
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        return matrix->data[row][col];
    } else {
        return 0.0;
    }
}

void printMatrix(const Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(const Matrix *matrix, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%lf ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

Matrix readMatrixFromFile(const char *filename) {
    Matrix matrix;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        matrix.rows = 0;
        matrix.cols = 0;
        matrix.data = NULL;
        return matrix;
    }

    fscanf(file, "%d %d", &matrix.rows, &matrix.cols);
    matrix = createMatrix(matrix.rows, matrix.cols);

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            fscanf(file, "%lf", &matrix.data[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

Matrix addMatrices(const Matrix *matrix1, const Matrix *matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Error! Matrix sizes do not match.\n");
        Matrix emptyMatrix;
        emptyMatrix.rows = 0;
        emptyMatrix.cols = 0;
        emptyMatrix.data = NULL;
        return emptyMatrix;
    }

    Matrix result = createMatrix(matrix1->rows, matrix1->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result.data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }

    return result;
}

Matrix subtractMatrices(const Matrix *matrix1, const Matrix *matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Error! Matrix sizes do not match.\n");
        Matrix emptyMatrix;
        emptyMatrix.rows = 0;
        emptyMatrix.cols = 0;
        emptyMatrix.data = NULL;
        return emptyMatrix;
    }

    Matrix result = createMatrix(matrix1->rows, matrix1->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result.data[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
        }
    }
    return result;
}

Matrix multiplyMatrixByScalar(const Matrix *matrix, double scalar) {
    Matrix result = createMatrix(matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result.data[i][j] = matrix->data[i][j] * scalar;
        }
    }

    return result;
}

Matrix multiplyMatrices(const Matrix *matrix1, const Matrix *matrix2) {
    if (matrix1->cols != matrix2->rows) {
        printf("Error! Matrix columns amount do not match.\n");
        Matrix emptyMatrix;
        emptyMatrix.rows = 0;
        emptyMatrix.cols = 0;
        emptyMatrix.data = NULL;
        return emptyMatrix;
    }

    Matrix result = createMatrix(matrix1->rows, matrix2->cols);

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < matrix1->cols; k++) {
                result.data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return result;
}