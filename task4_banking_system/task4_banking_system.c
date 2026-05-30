/*
 * CodeAlpha C Programming Internship
 * Task 4: High - Banking System (Mini Project)
 * Author: Eugine Bhebhe
 * Student ID: CA/DF1/52319
 *
 * Description: A Bank Account Management System in C.
 *              Functions: Create Account, Deposit, Withdraw,
 *              Balance Enquiry, Transaction History, and Exit.
 *              Uses structures, functions, and file handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ACCOUNTS_FILE     "accounts.dat"
#define TRANSACTIONS_FILE "transactions.dat"
#define MAX_NAME          60
#define MAX_TRANS         10

/* ================================================================
   STRUCTURES
   ================================================================ */
typedef struct {
    long   accountNumber;
    char   holderName[MAX_NAME];
    char   accountType[15];   /* "Savings" or "Current" */
    double balance;
    char   pin[5];            /* 4-digit PIN */
} Account;

typedef struct {
    long   accountNumber;
    char   type[15];          /* "Deposit" or "Withdrawal" */
    double amount;
    double balanceAfter;
    char   timestamp[30];
} Transaction;

/* ================================================================
   SAFE INPUT HELPERS
   Every scanf in this program goes through one of these three
   functions so there is NO leftover garbage in the buffer anywhere.
   ================================================================ */

/* Flush everything remaining on the current input line */
void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Read an integer safely. Retries until the user enters a valid one. */
int readInt(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            flushBuffer();   /* clear the '\n' left after the number */
            return value;
        }
        /* scanf failed - non-numeric input was entered */
        flushBuffer();
        printf("  Invalid input. Please enter a whole number.\n");
    }
}

/* Read a long safely. */
long readLong(const char *prompt) {
    long value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%ld", &value) == 1) {
            flushBuffer();
            return value;
        }
        flushBuffer();
        printf("  Invalid input. Please enter a valid number.\n");
    }
}

/* Read a double safely. */
double readDouble(const char *prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1) {
            flushBuffer();
            return value;
        }
        flushBuffer();
        printf("  Invalid input. Please enter a valid amount.\n");
    }
}

/* Read a string (fgets-based, trims the trailing newline). */
void readString(const char *prompt, char *buf, int size) {
    printf("%s", prompt);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

/* ================================================================
   UTILITY
   ================================================================ */
void printBanner() {
    printf("\n==========================================\n");
    printf("    CODEALPHA BANK MANAGEMENT SYSTEM      \n");
    printf("        Your Trusted Banking Partner      \n");
    printf("==========================================\n");
}

void printDivider() {
    printf("------------------------------------------\n");
}

void getTimestamp(char *buf) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, 30, "%Y-%m-%d %H:%M:%S", tm_info);
}

/* ================================================================
   FILE OPERATIONS
   ================================================================ */
long generateAccountNumber() {
    FILE *fp = fopen(ACCOUNTS_FILE, "rb");
    if (!fp) return 1000000001L;

    Account a;
    long count = 0;
    while (fread(&a, sizeof(Account), 1, fp)) count++;
    fclose(fp);
    return 1000000001L + count;
}

int findAccount(long accNo, Account *out) {
    FILE *fp = fopen(ACCOUNTS_FILE, "rb");
    if (!fp) return 0;

    Account a;
    while (fread(&a, sizeof(Account), 1, fp)) {
        if (a.accountNumber == accNo) {
            *out = a;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int updateAccount(Account updated) {
    FILE *fp = fopen(ACCOUNTS_FILE, "r+b");
    if (!fp) return 0;

    Account a;
    while (fread(&a, sizeof(Account), 1, fp)) {
        if (a.accountNumber == updated.accountNumber) {
            fseek(fp, -(long)sizeof(Account), SEEK_CUR);
            fwrite(&updated, sizeof(Account), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void logTransaction(long accNo, const char *type, double amount, double balAfter) {
    Transaction t;
    t.accountNumber = accNo;
    strncpy(t.type, type, sizeof(t.type) - 1);
    t.type[sizeof(t.type) - 1] = '\0';
    t.amount       = amount;
    t.balanceAfter = balAfter;
    getTimestamp(t.timestamp);

    FILE *fp = fopen(TRANSACTIONS_FILE, "ab");
    if (fp) {
        fwrite(&t, sizeof(Transaction), 1, fp);
        fclose(fp);
    }
}

/* ================================================================
   PIN VERIFICATION
   ================================================================ */
int verifyPIN(Account *a) {
    char entered[10];
    readString("  Enter 4-digit PIN: ", entered, sizeof(entered));
    return strcmp(entered, a->pin) == 0;
}

/* ================================================================
   FEATURES
   ================================================================ */
void createAccount() {
    Account a;
    a.accountNumber = generateAccountNumber();

    printf("\n--- CREATE NEW ACCOUNT ---\n");
    printf("  Account Number (auto-assigned): %ld\n", a.accountNumber);

    readString("  Enter Full Name:  ", a.holderName, MAX_NAME);

    int typeChoice = readInt("  Account Type:\n    1. Savings\n    2. Current\n  Choice: ");
    strcpy(a.accountType, (typeChoice == 2) ? "Current" : "Savings");

    double deposit;
    while (1) {
        deposit = readDouble("  Initial Deposit (minimum R100): R");
        if (deposit >= 100) break;
        printf("  Initial deposit must be at least R100. Try again.\n");
    }
    a.balance = deposit;

    readString("  Set a 4-digit PIN: ", a.pin, sizeof(a.pin));

    FILE *fp = fopen(ACCOUNTS_FILE, "ab");
    if (!fp) {
        printf("\n  Error: Could not save account!\n");
        return;
    }
    fwrite(&a, sizeof(Account), 1, fp);
    fclose(fp);

    logTransaction(a.accountNumber, "Deposit", a.balance, a.balance);

    printf("\n  Account created successfully!\n");
    printDivider();
    printf("  Account Number : %ld\n",   a.accountNumber);
    printf("  Account Holder : %s\n",    a.holderName);
    printf("  Account Type   : %s\n",    a.accountType);
    printf("  Opening Balance: R%.2f\n", a.balance);
    printDivider();
    printf("  NOTE: Remember your Account Number and PIN.\n");
}

void depositMoney() {
    printf("\n--- DEPOSIT ---\n");

    long accNo = readLong("  Enter Account Number: ");
    Account a;
    if (!findAccount(accNo, &a)) {
        printf("\n  Account not found.\n");
        return;
    }

    if (!verifyPIN(&a)) {
        printf("\n  Incorrect PIN. Access denied.\n");
        return;
    }

    double amount;
    while (1) {
        amount = readDouble("  Enter deposit amount: R");
        if (amount > 0) break;
        printf("  Amount must be greater than zero.\n");
    }

    a.balance += amount;
    updateAccount(a);
    logTransaction(accNo, "Deposit", amount, a.balance);

    printf("\n  Deposit successful!\n");
    printf("  Deposited  : R%.2f\n",   amount);
    printf("  New Balance: R%.2f\n",   a.balance);
}

void withdrawMoney() {
    printf("\n--- WITHDRAWAL ---\n");

    long accNo = readLong("  Enter Account Number: ");
    Account a;
    if (!findAccount(accNo, &a)) {
        printf("\n  Account not found.\n");
        return;
    }

    if (!verifyPIN(&a)) {
        printf("\n  Incorrect PIN. Access denied.\n");
        return;
    }

    double amount;
    while (1) {
        amount = readDouble("  Enter withdrawal amount: R");
        if (amount <= 0) {
            printf("  Amount must be greater than zero.\n");
            continue;
        }
        if (amount > a.balance) {
            printf("  Insufficient funds! Available balance: R%.2f\n", a.balance);
            continue;
        }
        if (strcmp(a.accountType, "Savings") == 0 && (a.balance - amount) < 100) {
            printf("  Savings accounts must keep a minimum balance of R100.\n");
            printf("  Maximum you can withdraw: R%.2f\n", a.balance - 100);
            continue;
        }
        break;
    }

    a.balance -= amount;
    updateAccount(a);
    logTransaction(accNo, "Withdrawal", amount, a.balance);

    printf("\n  Withdrawal successful!\n");
    printf("  Withdrawn  : R%.2f\n", amount);
    printf("  New Balance: R%.2f\n", a.balance);
}

void balanceEnquiry() {
    printf("\n--- BALANCE ENQUIRY ---\n");

    long accNo = readLong("  Enter Account Number: ");
    Account a;
    if (!findAccount(accNo, &a)) {
        printf("\n  Account not found.\n");
        return;
    }

    if (!verifyPIN(&a)) {
        printf("\n  Incorrect PIN. Access denied.\n");
        return;
    }

    printDivider();
    printf("  Account Number : %ld\n",   a.accountNumber);
    printf("  Account Holder : %s\n",    a.holderName);
    printf("  Account Type   : %s\n",    a.accountType);
    printf("  Current Balance: R%.2f\n", a.balance);
    printDivider();
}

void transactionHistory() {
    printf("\n--- TRANSACTION HISTORY ---\n");

    long accNo = readLong("  Enter Account Number: ");
    Account a;
    if (!findAccount(accNo, &a)) {
        printf("\n  Account not found.\n");
        return;
    }

    if (!verifyPIN(&a)) {
        printf("\n  Incorrect PIN. Access denied.\n");
        return;
    }

    FILE *fp = fopen(TRANSACTIONS_FILE, "rb");
    if (!fp) {
        printf("\n  No transaction history found.\n");
        return;
    }

    Transaction history[1000];
    int count = 0;
    Transaction t;
    while (fread(&t, sizeof(Transaction), 1, fp)) {
        if (t.accountNumber == accNo && count < 1000)
            history[count++] = t;
    }
    fclose(fp);

    if (count == 0) {
        printf("\n  No transactions found for this account.\n");
        return;
    }

    int show = (count < MAX_TRANS) ? count : MAX_TRANS;
    printf("\n  Last %d transaction(s) for Account %ld:\n", show, accNo);
    printDivider();
    printf("  %-12s  %-20s  %-12s  %s\n",
           "Type", "Timestamp", "Amount", "Balance After");
    printDivider();

    int start = (count > MAX_TRANS) ? count - MAX_TRANS : 0;
    for (int i = start; i < count; i++) {
        printf("  %-12s  %-20s  R%-11.2f  R%.2f\n",
               history[i].type,
               history[i].timestamp,
               history[i].amount,
               history[i].balanceAfter);
    }
    printDivider();
}

/* ================================================================
   MAIN
   ================================================================ */
int main() {
    printBanner();

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("  1. Create Account\n");
        printf("  2. Deposit\n");
        printf("  3. Withdraw\n");
        printf("  4. Balance Enquiry\n");
        printf("  5. Transaction History\n");
        printf("  6. Exit\n");

        int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: createAccount();      break;
            case 2: depositMoney();       break;
            case 3: withdrawMoney();      break;
            case 4: balanceEnquiry();     break;
            case 5: transactionHistory(); break;
            case 6:
                printf("\nThank you for banking with CodeAlpha Bank. Goodbye!\n\n");
                return 0;
            default:
                printf("  Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}