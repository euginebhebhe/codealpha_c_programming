/*
 * CodeAlpha C Programming Internship
 * Task 3: High – Student Management System
 * Author: Eugine Bhebhe
 * Student ID: CA/DF1/52319
 *
 * Description: A menu-driven student record management system.
 *              Features: Add, Delete, Update, Search, Display records.
 *              Uses structures + file handling for permanent storage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define MAX_NAME  50
#define MAX_COURSE 50

/* ── Structure ────────────────────────────────────────────── */
typedef struct {
    int    id;
    char   name[MAX_NAME];
    char   course[MAX_COURSE];
    int    age;
    float  gpa;
} Student;

/* ── Helpers ──────────────────────────────────────────────── */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printDivider() {
    printf("\n------------------------------------------------------------\n");
}

void printHeader() {
    printDivider();
    printf("  %-6s %-20s %-15s %-5s %-5s\n",
           "ID", "Name", "Course", "Age", "GPA");
    printDivider();
}

void printStudent(Student s) {
    printf("  %-6d %-20s %-15s %-5d %.2f\n",
           s.id, s.name, s.course, s.age, s.gpa);
}

int studentExists(int id) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int getNextID() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 1;

    Student s;
    int maxID = 0;
    while (fread(&s, sizeof(Student), 1, fp))
        if (s.id > maxID) maxID = s.id;

    fclose(fp);
    return maxID + 1;
}

/* ── CRUD Operations ──────────────────────────────────────── */
void addStudent() {
    Student s;
    s.id = getNextID();

    printf("\n--- ADD STUDENT ---\n");
    printf("Auto-assigned ID: %d\n", s.id);

    printf("Enter Name:   ");
    clearInputBuffer();
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Course: ");
    fgets(s.course, MAX_COURSE, stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter Age:    ");
    scanf("%d", &s.age);

    printf("Enter GPA:    ");
    scanf("%f", &s.gpa);

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("\nError: Could not open file!\n");
        return;
    }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\n✅ Student '%s' added successfully with ID: %d\n", s.name, s.id);
}

void displayAllStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nNo records found. The database is empty.\n");
        return;
    }

    printf("\n--- ALL STUDENT RECORDS ---");
    printHeader();

    Student s;
    int count = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        printStudent(s);
        count++;
    }
    fclose(fp);
    printDivider();
    printf("  Total Records: %d\n", count);
}

void searchStudent() {
    int id;
    printf("\n--- SEARCH STUDENT ---\n");
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nNo records found.\n");
        return;
    }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("\n✅ Student Found:");
            printHeader();
            printStudent(s);
            printDivider();
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\n❌ Student with ID %d not found.\n", id);
}

void updateStudent() {
    int id;
    printf("\n--- UPDATE STUDENT ---\n");
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r+b");
    if (!fp) {
        printf("\nNo records found.\n");
        return;
    }

    Student s;
    int found = 0;
    long pos;

    while ((pos = ftell(fp)), fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            printf("\nCurrent Record:");
            printHeader();
            printStudent(s);
            printDivider();

            printf("\nEnter new Name   [%s]: ", s.name);
            clearInputBuffer();
            char temp[MAX_NAME];
            fgets(temp, MAX_NAME, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) strcpy(s.name, temp);

            printf("Enter new Course [%s]: ", s.course);
            fgets(temp, MAX_COURSE, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) strcpy(s.course, temp);

            printf("Enter new Age    [%d]: ", s.age);
            int newAge;
            scanf("%d", &newAge);
            if (newAge > 0) s.age = newAge;

            printf("Enter new GPA    [%.2f]: ", s.gpa);
            float newGpa;
            scanf("%f", &newGpa);
            if (newGpa >= 0) s.gpa = newGpa;

            fseek(fp, pos, SEEK_SET);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("\n✅ Student record updated successfully!\n");
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\n❌ Student with ID %d not found.\n", id);
}

void deleteStudent() {
    int id;
    printf("\n--- DELETE STUDENT ---\n");
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nNo records found.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("\nError creating temp file!\n");
        fclose(fp);
        return;
    }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            printf("\nDeleting record:");
            printHeader();
            printStudent(s);
            printDivider();
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\n✅ Student with ID %d deleted successfully!\n", id);
    else
        printf("\n❌ Student with ID %d not found.\n", id);
}

/* ── Main ─────────────────────────────────────────────────── */
int main() {
    int choice;
    char again;

    printf("\n========================================\n");
    printf("   CODEALPHA STUDENT MANAGEMENT SYSTEM  \n");
    printf("========================================\n");

    do {
        printf("\n--- MAIN MENU ---\n");
        printf("  1. Add Student\n");
        printf("  2. Display All Students\n");
        printf("  3. Search Student\n");
        printf("  4. Update Student\n");
        printf("  5. Delete Student\n");
        printf("  6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();        break;
            case 2: displayAllStudents();break;
            case 3: searchStudent();     break;
            case 4: updateStudent();     break;
            case 5: deleteStudent();     break;
            case 6:
                printf("\nExiting Student Management System. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\nReturn to main menu? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    printf("\nThank you for using CodeAlpha Student Management System!\n");
    return 0;
}
