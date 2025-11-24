#include <iostream>
#include <string>
#include "DataBase.h"
#include "ConsistencyChecker.h"
#include "CourseScheduling.h"
#include "InductionModule.h"
#include "Logic&InferenceModule.h"
#include "FunctionsModule.h"
#include "RelationsModule.h"
#include "SetOperationsModule.h"
#include "StudentGroupModule.h"
using namespace std;

// Global database instance
DataBase db;

// Function prototypes
void mainMenu();
void dataManagementMenu();
void studentMenu();
void courseMenu();
void facultyMenu();
void enrollmentMenu();
void verificationMenu();
void consistencyCheckMenu();
void inductionMenu();
void logicMenu();
void discreteMathMenu();
void displayBanner();
void pauseScreen();

int main()
{
    displayBanner();

    // Load existing data
    cout << "Loading existing data from 'data' directory...\n";
    db.loadAllData("data");

    mainMenu();

    // Save data before exit
    cout << "\nSaving all data...\n";
    db.saveAllData("data");

    cout << "\nThank you for using our little project not little though\n";
    cout << "Developed for FAST University - Discrete Mathematics Project\n\n";

    return 0;
}

void displayBanner()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                            ║\n";
    cout << "║              University Management System                  ║\n";
    cout << "║         Based on Discrete Mathematics Concepts             ║\n";
    cout << "║                                                            ║\n";
    cout << "║                  FAST University                           ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void mainMenu()
{
    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║                        MAIN MENU                           ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Data Management                                        ║\n";
        cout << "║  2. Consistency & Verification                             ║\n";
        cout << "║  3. Induction & Proof Generation                           ║\n";
        cout << "║  4. Logic & Inference Engine                               ║\n";
        cout << "║  5. Discrete Mathematics Modules                           ║\n";
        cout << "║  6. Generate Reports                                       ║\n";
        cout << "║  0. Exit                                                   ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            dataManagementMenu();
            break;
        case 2:
            verificationMenu();
            break;
        case 3:
            inductionMenu();
            break;
        case 4:
            logicMenu();
            break;
        case 5:
            discreteMathMenu();
            break;
        case 6:
            cout << "\n=== Generating Reports ===\n";
            db.displayAllStudents();
            db.displayAllCourses();
            db.displayAllFaculty();
            pauseScreen();
            break;
        case 0:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\n Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
}

void dataManagementMenu()
{
    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║                  DATA MANAGEMENT MENU                      ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Student Management                                     ║\n";
        cout << "║  2. Course Management                                      ║\n";
        cout << "║  3. Faculty Management                                     ║\n";
        cout << "║  4. Enrollment Management                                  ║\n";
        cout << "║  5. Load Data from Files                                   ║\n";
        cout << "║  6. Save Data to Files                                     ║\n";
        cout << "║  0. Back to Main Menu                                      ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            studentMenu();
            break;
        case 2:
            courseMenu();
            break;
        case 3:
            facultyMenu();
            break;
        case 4:
            enrollmentMenu();
            break;
        case 5:
            db.loadAllData("data");
            pauseScreen();
            break;
        case 6:
            db.saveAllData("data");
            pauseScreen();
            break;
        case 0:
            break;
        default:
            cout << "\n Invalid choice!\n";
        }
    } while (choice != 0);
}

void studentMenu()
{
    int choice;
    do
    {
        cout << "\n=== STUDENT MANAGEMENT ===\n";
        cout << "1. Add New Student\n";
        cout << "2. View Student Details\n";
        cout << "3. View All Students\n";
        cout << "4. Add Completed Course\n";
        cout << "5. Check Available Courses\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string id, name, dept;
            int year;
            cout << "Enter Student ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Department: ";
            getline(cin, dept);
            cout << "Enter Year: ";
            cin >> year;
            cin.ignore();

            Student s(id, name, dept, year);
            db.addStudent(s);
            cout << " Student added successfully!\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            cout << "Enter Student ID: ";
            getline(cin, id);

            Student* s = db.getStudent(id);
            if (s)
            {
                s->display();
            }
            else
            {
                cout << " Student not found!\n";
            }
            pauseScreen();
            break;
        }
        case 3:
            db.displayAllStudents();
            pauseScreen();
            break;
        case 4:
        {
            string studentId, courseId;
            cout << "Enter Student ID: ";
            getline(cin, studentId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            Student* s = db.getStudent(studentId);
            if (s)
            {
                s->addCompletedCourse(courseId);
                cout << " Course added to completed courses!\n";
            }
            else
            {
                cout << " Student not found!\n";
            }
            pauseScreen();
            break;
        }
        case 5:
        {
            string studentId;
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            vector<string> available = db.getAvailableCourses(studentId);
            cout << "\nAvailable Courses for Student " << studentId << ":\n";
            for (const string& c : available)
            {
                cout << "  - " << c << endl;
            }
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}

void courseMenu()
{
    int choice;
    do
    {
        cout << "\n=== COURSE MANAGEMENT ===\n";
        cout << "1. Add New Course\n";
        cout << "2. View Course Details\n";
        cout << "3. View All Courses\n";
        cout << "4. Add Prerequisite\n";
        cout << "5. View Course Prerequisites (Transitive)\n";
        cout << "6. Generate Valid Course Sequence\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string id, name;
            int credits;
            cout << "Enter Course ID: ";
            getline(cin, id);
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Credits: ";
            cin >> credits;
            cin.ignore();

            Courses c(id, name, credits);
            db.addCourse(c);
            cout << " Course added successfully!\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            cout << "Enter Course ID: ";
            getline(cin, id);

            Courses* c = db.getCourse(id);
            if (c)
            {
                c->display();
            }
            else
            {
                cout << " Course not found!\n";
            }
            pauseScreen();
            break;
        }
        case 3:
            db.displayAllCourses();
            pauseScreen();
            break;
        case 4:
        {
            string courseId, prereqId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Prerequisite Course ID: ";
            getline(cin, prereqId);

            Courses* c = db.getCourse(courseId);
            if (c)
            {
                c->addPrerequisite(prereqId);
                db.buildPrerequisiteGraph();
                cout << " Prerequisite added!\n";
            }
            else
            {
                cout << " Course not found!\n";
            }
            pauseScreen();
            break;
        }
        case 5:
        {
            string courseId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            set<string> allPrereqs = db.getAllPrerequisites(courseId);
            cout << "\nAll Prerequisites (including indirect) for " << courseId << ":\n";
            for (const string& p : allPrereqs)
            {
                cout << "  - " << p << endl;
            }
            pauseScreen();
            break;
        }
        case 6:
        {
            vector<string> sequence = db.getValidCourseSequence();
            cout << "\nValid Course Sequence (Topological Order):\n";
            for (size_t i = 0; i < sequence.size(); i++)
            {
                cout << (i + 1) << ". " << sequence[i] << endl;
            }
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}

void facultyMenu()
{
    int choice;
    do
    {
        cout << "\n=== FACULTY MANAGEMENT ===\n";
        cout << "1. Add New Faculty\n";
        cout << "2. View Faculty Details\n";
        cout << "3. View All Faculty\n";
        cout << "4. Assign Course to Faculty\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string id, name, dept;
            cout << "Enter Faculty ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Department: ";
            getline(cin, dept);

            Faculty f(id, name, dept);
            db.addFaculty(f);
            cout << "✓ Faculty added successfully!\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            cout << "Enter Faculty ID: ";
            getline(cin, id);

            Faculty* f = db.getFaculty(id);
            if (f)
            {
                f->display();
            }
            else
            {
                cout << " Faculty not found!\n";
            }
            pauseScreen();
            break;
        }
        case 3:
            db.displayAllFaculty();
            pauseScreen();
            break;
        case 4:
        {
            string facultyId, courseId;
            cout << "Enter Faculty ID: ";
            getline(cin, facultyId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            Faculty* f = db.getFaculty(facultyId);
            if (f)
            {
                f->assignCourse(courseId);
                cout << " Course assigned to faculty!\n";
            }
            else
            {
                cout << " Faculty not found!\n";
            }
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}

void enrollmentMenu()
{
    int choice;
    do
    {
        cout << "\n=== ENROLLMENT MANAGEMENT ===\n";
        cout << "1. Enroll Student in Course\n";
        cout << "2. View Student's Courses\n";
        cout << "3. View Course's Students\n";
        cout << "4. Check Enrollment Eligibility\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string studentId, courseId, timeSlotId, semesterId;
            cout << "Enter Student ID: ";
            getline(cin, studentId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter TimeSlot ID: ";
            getline(cin, timeSlotId);
            cout << "Enter Semester ID: ";
            getline(cin, semesterId);

            Enrollment e(studentId, courseId, timeSlotId, semesterId);
            db.addEnrollment(e);
            cout << " Enrollment added!\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            string studentId;
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            vector<string> courses = db.getStudentCourses(studentId);
            cout << "\nCourses for Student " << studentId << ":\n";
            for (const string& c : courses)
            {
                cout << "  - " << c << endl;
            }
            pauseScreen();
            break;
        }
        case 3:
        {
            string courseId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            vector<string> students = db.getEnrolledStudents(courseId);
            cout << "\nStudents enrolled in " << courseId << ":\n";
            for (const string& s : students)
            {
                cout << "  - " << s << endl;
            }
            pauseScreen();
            break;
        }
        case 4:
        {
            string studentId, courseId;
            cout << "Enter Student ID: ";
            getline(cin, studentId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            if (db.canEnroll(studentId, courseId))
            {
                cout << " Student CAN enroll in this course!\n";
            }
            else
            {
                cout << " Student CANNOT enroll - prerequisites not met!\n";
            }
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}

void verificationMenu()
{
    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║              CONSISTENCY & VERIFICATION MENU               ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Check Missing Prerequisites                            ║\n";
        cout << "║  2. Detect Circular Prerequisites                          ║\n";
        cout << "║  3. Validate Student Schedule Conflicts                    ║\n";
        cout << "║  4. Check Room Double Booking                              ║\n";
        cout << "║  5. Check Student Overload                                 ║\n";
        cout << "║  6. Run All Consistency Checks                             ║\n";
        cout << "║  0. Back to Main Menu                                      ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        ConsistencyChecker checker;

        switch (choice)
        {
        case 1:
        {
            cout << "\n=== Checking Missing Prerequisites ===\n";
            // Build data structures for check
            map<string, vector<string>> prereqs;
            map<string, set<string>> studentCourses;

            // This is a simplified example - you'd need to populate these from db
            cout << " Feature requires additional data setup\n";
            pauseScreen();
            break;
        }
        case 2:
        {
            cout << "\n=== Detecting Circular Prerequisites ===\n";
            if (db.hasCircularDependency())
            {
                cout << " CIRCULAR DEPENDENCY DETECTED!\n";
                cout << "This is a critical error that must be fixed.\n";
            }
            else
            {
                cout << "✓ No circular dependencies found.\n";
            }
            pauseScreen();
            break;
        }
        case 6:
        {
            cout << "\n╔════════════════════════════════════════════════════════════╗\n";
            cout << "║              RUNNING ALL CONSISTENCY CHECKS                ║\n";
            cout << "╚════════════════════════════════════════════════════════════╝\n\n";

            cout << "1. Circular Dependency Check: ";
            if (db.hasCircularDependency())
            {
                cout << "❌ FAILED\n";
            }
            else
            {
                cout << "✓ PASSED\n";
            }

            cout << "\n✓ All checks completed!\n";
            pauseScreen();
            break;
        }
        case 0:
            break;
        default:
            cout << "\n⚠ Invalid choice!\n";
        }
    } while (choice != 0);
}

void inductionMenu()
{
    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║            INDUCTION & PROOF GENERATION MENU               ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Verify Prerequisite Chain (Simple Induction)           ║\n";
        cout << "║  2. Generate Induction Proof                               ║\n";
        cout << "║  3. Verify with Strong Induction                           ║\n";
        cout << "║  4. Generate Strong Induction Proof                        ║\n";
        cout << "║  5. Display Prerequisite Chain Tree                        ║\n";
        cout << "║  0. Back to Main Menu                                      ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        InductionModule inductionModule(&db);

        switch (choice)
        {
        case 1:
        {
            string courseId, studentId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            if (inductionModule.verifyPrerequisiteChain(courseId, studentId))
            {
                cout << "\n✓ All prerequisites verified!\n";
            }
            else
            {
                cout << "\n⚠ Prerequisites not satisfied!\n";
            }
            pauseScreen();
            break;
        }
        case 2:
        {
            string courseId, studentId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            InductionModule::Proof proof = inductionModule.generateInductionProof(courseId, studentId);
            proof.display();
            pauseScreen();
            break;
        }
        case 3:
        {
            string courseId, studentId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            if (inductionModule.verifyWithStrongInduction(courseId, studentId))
            {
                cout << "\n✓ Strong induction verification PASSED!\n";
            }
            else
            {
                cout << "\n⚠ Strong induction verification FAILED!\n";
            }
            pauseScreen();
            break;
        }
        case 4:
        {
            string courseId, studentId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            InductionModule::Proof proof = inductionModule.generateStrongInductionProof(courseId, studentId);
            proof.display();
            pauseScreen();
            break;
        }
        case 5:
        {
            string courseId;
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            cout << "\n=== Prerequisite Chain Tree ===\n";
            inductionModule.displayPrerequisiteChain(courseId);
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}

void logicMenu()
{
    int choice;
    LogicEngine logicEngine(&db);

    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║              LOGIC & INFERENCE ENGINE MENU                 ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Add Logical Rule                                       ║\n";
        cout << "║  2. Add Fact                                               ║\n";
        cout << "║  3. Display All Rules                                      ║\n";
        cout << "║  4. Display All Facts                                      ║\n";
        cout << "║  5. Perform Inference (Modus Ponens, etc.)                 ║\n";
        cout << "║  6. Detect Conflicts                                       ║\n";
        cout << "║  7. Generate Truth Table                                   ║\n";
        cout << "║  8. Load Rules from File                                   ║\n";
        cout << "║  9. Save Rules to File                                     ║\n";
        cout << "║  10. Display Statistics                                    ║\n";
        cout << "║  0. Back to Main Menu                                      ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string condition, consequence, ruleType;
            cout << "Enter condition (IF part): ";
            getline(cin, condition);
            cout << "Enter consequence (THEN part): ";
            getline(cin, consequence);
            cout << "Enter rule type (IMPLIES/AND/OR/NOT): ";
            getline(cin, ruleType);

            string ruleId = logicEngine.addRule(condition, consequence, ruleType);
            cout << "✓ Rule added with ID: " << ruleId << endl;
            pauseScreen();
            break;
        }
        case 2:
        {
            string statement;
            char truthChar;
            cout << "Enter statement: ";
            getline(cin, statement);
            cout << "Is it true? (y/n): ";
            cin >> truthChar;
            cin.ignore();

            bool truthValue = (truthChar == 'y' || truthChar == 'Y');
            string factId = logicEngine.addFact(statement, truthValue);
            cout << "✓ Fact added with ID: " << factId << endl;
            pauseScreen();
            break;
        }
        case 3:
            logicEngine.displayAllRules();
            pauseScreen();
            break;
        case 4:
            logicEngine.displayAllFacts();
            pauseScreen();
            break;
        case 5:
            logicEngine.performInference();
            pauseScreen();
            break;
        case 6:
            logicEngine.detectAllConflicts();
            logicEngine.displayConflicts();
            pauseScreen();
            break;
        case 7:
        {
            string expression;
            cout << "Enter logical expression: ";
            getline(cin, expression);

            vector<string> vars;
            logicEngine.displayTruthTable(expression, vars);
            pauseScreen();
            break;
        }
        case 8:
        {
            string filename;
            cout << "Enter filename: ";
            getline(cin, filename);
            logicEngine.loadRulesFromFile(filename);
            pauseScreen();
            break;
        }
        case 9:
        {
            string filename;
            cout << "Enter filename: ";
            getline(cin, filename);
            logicEngine.saveRulesToFile(filename);
            pauseScreen();
            break;
        }
        case 10:
            logicEngine.displayStatistics();
            pauseScreen();
            break;
        }
    } while (choice != 0);
}

void discreteMathMenu()
{
    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║            DISCRETE MATHEMATICS MODULES MENU               ║\n";
        cout << "╠════════════════════════════════════════════════════════════╣\n";
        cout << "║  1. Set Operations Demonstration                           ║\n";
        cout << "║  2. Relations Demonstration                                ║\n";
        cout << "║  3. Functions Demonstration                                ║\n";
        cout << "║  4. Student Group Combinations                             ║\n";
        cout << "║  0. Back to Main Menu                                      ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            SetOperations::demonstrateSetOperations();
            pauseScreen();
            break;
        case 2:
            RelationsModule::demonstrateRelations();
            pauseScreen();
            break;
        case 3:
            FunctionsModule::demonstrateFunctions();
            pauseScreen();
            break;
        case 4:
        {
            GroupGenerator generator;

            cout << "\n=== Student Group Combinations ===\n";
            cout << "1. Generate all possible groups\n";
            cout << "2. Form project groups (sequential)\n";
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
            {
                int groupSize, numStudents;
                cout << "Enter number of students: ";
                cin >> numStudents;
                cout << "Enter group size: ";
                cin >> groupSize;
                cin.ignore();

                vector<string> students;
                for (int i = 1; i <= numStudents; i++)
                {
                    students.push_back("S" + to_string(i));
                }

                generator.displayCombinationStats(numStudents, groupSize);

                vector<GroupGenerator::Group> groups = generator.generateAllCombinations(students, groupSize);
                generator.displayGroups(groups);
            }
            else if (subChoice == 2)
            {
                int groupSize, numStudents;
                cout << "Enter number of students: ";
                cin >> numStudents;
                cout << "Enter group size: ";
                cin >> groupSize;
                cin.ignore();

                vector<string> students;
                for (int i = 1; i <= numStudents; i++)
                {
                    students.push_back("S" + to_string(i));
                }

                vector<GroupGenerator::Group> groups = generator.formProjectGroups(students, groupSize);
                generator.displayGroups(groups);
            }
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}