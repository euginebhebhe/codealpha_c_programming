/*
 * CodeAlpha C Programming Internship
 * Task 1: Basic – Calculator Program
 * Author: Eugine Bhebhe
 * Student ID: CA/DF1/52319
 *
 * Description: A menu-driven calculator that performs basic arithmetic
 *              operations using switch-case.
 */

#include <stdio.h>

void printMenu() {
    printf("\n========================================\n");
    printf("        CODEALPHA CALCULATOR            \n");
    printf("========================================\n");
    printf("  1. Addition       (+)\n");
    printf("  2. Subtraction    (-)\n");
    printf("  3. Multiplication (*)\n");
    printf("  4. Division       (/)\n");
    printf("  5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    double num1, num2, result;
    char again;

    printf("\nWelcome to CodeAlpha Calculator!\n");

    do {
        printMenu();
        scanf("%d", &choice);

        if (choice == 5) {
            printf("\nThank you for using CodeAlpha Calculator. Goodbye!\n");
            break;
        }

        if (choice < 1 || choice > 4) {
            printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
            continue;
        }

        printf("Enter first number:  ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("\nResult: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 2:
                result = num1 - num2;
                printf("\nResult: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 3:
                result = num1 * num2;
                printf("\nResult: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 4:
                if (num2 == 0) {
                    printf("\nError: Division by zero is not allowed!\n");
                } else {
                    result = num1 / num2;
                    printf("\nResult: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
                }
                break;
        }

        printf("\nDo you want to perform another calculation? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    if (again != 'y' && again != 'Y') {
        printf("\nThank you for using CodeAlpha Calculator. Goodbye!\n");
    }

    return 0;
}
