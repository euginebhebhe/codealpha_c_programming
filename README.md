# CodeAlpha C Programming Internship Tasks

**Intern:** Eugine Bhebhe  
**Student ID:** CA/DF1/52319  
**Internship Period:** 1st May 2026 – 30th May 2026  
**Domain:** C Programming  

---

## Tasks Completed ✅

### Task 1 – Calculator Program (`task1_calculator.c`)
**Difficulty:** Basic  
A menu-driven calculator that performs the four basic arithmetic operations using `switch-case`.

**Features:**
- Addition, Subtraction, Multiplication, Division
- Division-by-zero error handling
- Loop to perform multiple calculations in one session

**Compile & Run:**
```bash
gcc -o calculator task1_calculator.c
./calculator
```

---

### Task 2 – Matrix Operations (`task2_matrix.c`)
**Difficulty:** Medium  
Implements three matrix operations using functions and 2D arrays.

**Features:**
- Matrix Addition (same-size matrices)
- Matrix Multiplication (compatible dimensions)
- Matrix Transpose
- Formatted matrix display

**Compile & Run:**
```bash
gcc -o matrix task2_matrix.c
./matrix
```

---

### Task 3 – Student Management System (`task3_student_management.c`)
**Difficulty:** High  
A full CRUD student record system with persistent file storage.

**Features:**
- Add student records (auto-incremented ID)
- Display all students
- Search student by ID
- Update student record
- Delete student record
- Data stored permanently in `students.dat`

**Compile & Run:**
```bash
gcc -o student_mgmt task3_student_management.c
./student_mgmt
```

---

### Task 4 – Banking System (`task4_banking_system.c`)
**Difficulty:** High  
A mini bank account management system with PIN authentication and transaction logging.

**Features:**
- Create account (auto-generated account number)
- Deposit money
- Withdraw money (with minimum balance enforcement for Savings accounts)
- Balance enquiry
- Transaction history (last 10 transactions)
- PIN-protected access
- Data stored in `accounts.dat` and `transactions.dat`

**Compile & Run:**
```bash
gcc -o banking task4_banking_system.c
./banking
```

---

## How to Compile All at Once

```bash
gcc -Wall -o calculator    task1_calculator.c
gcc -Wall -o matrix        task2_matrix.c
gcc -Wall -o student_mgmt  task3_student_management.c
gcc -Wall -o banking       task4_banking_system.c
```

---

## Technologies Used
- Language: **C (C99)**
- Concepts: Structures, File I/O, 2D Arrays, Functions, Switch-Case, Pointers, Loops

---

*CodeAlpha Internship — Your Dream Our Passion 💙*
