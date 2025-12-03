# University Management System (Discrete Mathematics Project)

## 📌 Project Overview
The **University Management System** is a comprehensive C++ application developed for the Discrete Mathematics course at **FAST University**. This project bridges the gap between theoretical discrete structures and practical software engineering. It utilizes concepts such as **Sets, Relations, Functions, Logic, Induction, and Graph Theory** to solve real-world university management problems like course scheduling, prerequisite verification, and student grouping.

## 👥 Team Members
* **Muhammad Hassan Ahmad**
* **Muhammad Ahmad**
* **Musfirah**

## 🚀 Key Features

### 1. Data Management
A robust system to manage core university entities with file persistence (`university_data.txt`).
* **Student Management**: Add/view students, manage completed courses.
* **Course Management**: Define credits, prerequisites, and valid sequences.
* **Faculty Management**: Assign courses and view faculty details.
* **Enrollment**: Handle student course registration with validation.

### 2. Logic & Inference Engine
A custom-built inference engine to validate academic policies.
* **Rule Management**: Define rules (IMPLIES, AND, OR, NOT).
* **Inference**: Applies **Modus Ponens**, **Modus Tollens**, and **Hypothetical Syllogism**.
* **Conflict Detection**: Identifies contradictory rules or facts.
* **Truth Tables**: Auto-generates truth tables for logical expressions.

### 3. Discrete Math Modules
Practical implementation of core mathematical structures:
* **Set Operations**: Union, Intersection, Difference, Power Sets, and Cartesian Products used for student grouping.
* **Relations Module**: Checks for Reflexivity, Symmetry, Transitivity, and Equivalence Relations. Includes **Warshall’s Algorithm** for transitive closures.
* **Functions Module**: Validates mappings (Injective, Surjective, Bijective) and handles function composition.

### 4. Induction & Proofs
* **Prerequisite Verification**: Uses **Mathematical Induction** to prove the validity of course chains.
* **Proof Generation**: Auto-generates step-by-step induction proofs for strong and weak induction scenarios.

### 5.  Consistency & Verification
* **Circular Dependency Check**: Detects cycles in course prerequisites using graph traversal.
* **Constraint Validation**: Checks for room double-booking and student workload overload.

### 6.  Algorithmic Efficiency
* **Complexity Analysis**: Built-in analyzer to evaluate the efficiency of database operations and consistency checks.
* **Optimization Reports**: Provides summaries on module performance.

##  Tech Stack
* **Language**: C++
* **Concepts**: OOP, STL (Vectors, Maps, Sets), Discrete Structures, Algorithms.
* **Environment**: Visual Studio / Standard C++ Compiler.

## How to Run
1.  Clone the repository.
2.  Open the solution file `Discrete End Sem.sln` in Visual Studio OR compile the source files using a C++ compiler (e.g., g++).
    ```bash
    g++ main.cpp DataBase.cpp ConsistencyChecker.cpp Logic&InferenceModule.cpp ... -o UniversitySystem
    ```
3.  Run the executable.
4.  Navigate the menu using the console interface.

---
*Developed as a semester project for Discrete Structures.*# Discrete End Sem
