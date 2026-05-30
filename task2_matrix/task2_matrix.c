/*
 * CodeAlpha C Programming Internship
 * Task 2: Medium – Matrix Operations
 * Author: Eugine Bhebhe
 * Student ID: CA/DF1/52319
 *
 * Description: Implements Matrix Addition, Multiplication, and Transpose
 *              using functions and 2D arrays.
 */

#include <stdio.h>

#define MAX 10

/* ── Utility ─────────────────────────────────────────────── */
void inputMatrix(int mat[MAX][MAX], int rows, int cols, const char *name) {
    printf("\nEnter elements of Matrix %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("  %s[%d][%d]: ", name, i + 1, j + 1);
            scanf("%d", &mat[i][j]);
        }
    }
}

void displayMatrix(int mat[MAX][MAX], int rows, int cols, const char *name) {
    printf("\nMatrix %s:\n", name);
    printf("  ");
    for (int j = 0; j < cols; j++) printf("------");
    printf("\n");
    for (int i = 0; i < rows; i++) {
        printf("  | ");
        for (int j = 0; j < cols; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("  ");
    for (int j = 0; j < cols; j++) printf("------");
    printf("\n");
}

/* ── Operations ───────────────────────────────────────────── */
void addMatrices(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrices(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX],
                      int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void transposeMatrix(int A[MAX][MAX], int T[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            T[j][i] = A[i][j];
}

/* ── Menu handlers ────────────────────────────────────────── */
void handleAddition() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int rows, cols;

    printf("\nEnter number of rows (max %d):    ", MAX);
    scanf("%d", &rows);
    printf("Enter number of columns (max %d): ", MAX);
    scanf("%d", &cols);

    inputMatrix(A, rows, cols, "A");
    inputMatrix(B, rows, cols, "B");

    addMatrices(A, B, C, rows, cols);

    displayMatrix(A, rows, cols, "A");
    displayMatrix(B, rows, cols, "B");
    printf("\nResult: A + B =");
    displayMatrix(C, rows, cols, "C");
}

void handleMultiplication() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int rowsA, colsA, colsB;

    printf("\nEnter rows of A (max %d):       ", MAX);
    scanf("%d", &rowsA);
    printf("Enter columns of A (max %d):    ", MAX);
    scanf("%d", &colsA);
    printf("Enter columns of B (max %d):    ", MAX);
    scanf("%d", &colsB);

    inputMatrix(A, rowsA, colsA, "A");
    inputMatrix(B, colsA, colsB, "B");

    multiplyMatrices(A, B, C, rowsA, colsA, colsB);

    displayMatrix(A, rowsA, colsA, "A");
    displayMatrix(B, colsA, colsB, "B");
    printf("\nResult: A x B =");
    displayMatrix(C, rowsA, colsB, "C");
}

void handleTranspose() {
    int A[MAX][MAX], T[MAX][MAX];
    int rows, cols;

    printf("\nEnter number of rows (max %d):    ", MAX);
    scanf("%d", &rows);
    printf("Enter number of columns (max %d): ", MAX);
    scanf("%d", &cols);

    inputMatrix(A, rows, cols, "A");
    transposeMatrix(A, T, rows, cols);

    displayMatrix(A, rows, cols, "A");
    printf("\nResult: Transpose of A =");
    displayMatrix(T, cols, rows, "T");
}

/* ── Main ─────────────────────────────────────────────────── */
int main() {
    int choice;
    char again;

    printf("\n========================================\n");
    printf("     CODEALPHA MATRIX OPERATIONS        \n");
    printf("========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("  1. Matrix Addition\n");
        printf("  2. Matrix Multiplication\n");
        printf("  3. Matrix Transpose\n");
        printf("  4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: handleAddition();       break;
            case 2: handleMultiplication(); break;
            case 3: handleTranspose();      break;
            case 4:
                printf("\nExiting Matrix Operations. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\nPerform another operation? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    printf("\nThank you for using CodeAlpha Matrix Operations. Goodbye!\n");
    return 0;
}
