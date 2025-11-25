#include <iostream>
#include <string>
#include <windows.h> 
#include "DataBase.h"
#include "ConsistencyChecker.h"
#include "CourseScheduling.h"
#include "InductionModule.h"
#include "Logic&InferenceModule.h"
#include "FunctionsModule.h"
#include "RelationsModule.h"
#include "SetOperationsModule.h"
#include "StudentGroupModule.h"
#include "AlgorithmicEfficiency.h"
using namespace std;

enum Color {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
    RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7,
    DARKGRAY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
    LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15
};

// Global database instance
DataBase db;

// Color scheme constants
const int MENU_BORDER_COLOR = LIGHTCYAN;
const int MENU_TITLE_COLOR = LIGHTMAGENTA;
const int MENU_OPTION_COLOR = WHITE;
const int MENU_HIGHLIGHT_COLOR = YELLOW;
const int SUCCESS_COLOR = LIGHTGREEN;
const int ERROR_COLOR = LIGHTRED;
const int INFO_COLOR = LIGHTCYAN;

// Function prototypes
void setcolor(int color);
void printCentered(string text, int width = 80);
void printBoxedText(string text, int color = CYAN);
void clearScreen();
void mainMenu();
void dataManagementMenu();
void studentMenu();
void courseMenu();
void facultyMenu();
void enrollmentMenu();
void verificationMenu()
void algorithmicEfficiencyMenu();
void inductionMenu();
void logicMenu();
void discreteMathMenu();
void displayBanner();
void pauseScreen();

void setcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printCentered(string text, int width)
{
    int padding = (width - text.length()) / 2;
    cout << string(padding, ' ') << text << endl;
}

void printBoxedText(string text, int color)
{
    setcolor(color);
    int width = text.length() + 4;
    cout << string(width, '=') << endl;
    cout << "| " << text << " |" << endl;
    cout << string(width, '=') << endl;
    setcolor(MENU_OPTION_COLOR);
}

void clearScreen()
{
    system("cls");
}

int main()
{
    displayBanner();
    setcolor(INFO_COLOR);
    cout << "Loading existing data...\n";
    db.loadFromFile("university_data.txt");
    setcolor(MENU_OPTION_COLOR);
    mainMenu();

    // Save data before exit
    setcolor(INFO_COLOR);
    cout << "\nSaving all data...\n";
    db.saveToFile("university_data.txt");

    cout << "\nThank you for using our University Management System\n";
    cout << "Developed for FAST University - Discrete Mathematics Project\n\n";
    setcolor(MENU_OPTION_COLOR);

    return 0;
}

void displayBanner()
{
    cout << "\n";
    setcolor(MENU_BORDER_COLOR);
    cout << "==============================================================\n";
    setcolor(MENU_TITLE_COLOR);
    cout << "|                                                            |\n";
    cout << "|              University Management System                  |\n";
    cout << "|         Based on Discrete Mathematics Concepts             |\n";
    cout << "|                                                            |\n";
    cout << "|                  FAST University                           |\n";
    cout << "|                                                            |\n";
    setcolor(MENU_BORDER_COLOR);
    cout << "==============================================================\n";
    cout << "\n";
    setcolor(MENU_OPTION_COLOR);
}

void pauseScreen()
{
    setcolor(MENU_HIGHLIGHT_COLOR);
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    setcolor(MENU_OPTION_COLOR);
}

void mainMenu()
{
    int choice;
    do
    {
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "                       MAIN MENU                            \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Data Management                                        \n";
        cout << "  2. Consistency & Verification                             \n";
        cout << "  3. Induction & Proof Generation                           \n";
        cout << "  4. Logic & Inference Engine                               \n";
        cout << "  5. Discrete Mathematics Modules                           \n";
        cout << "  6. Generate Reports                                       \n";
        cout << "  7. Algorithmic Efficiency Analysis                        \n";
        cout << "  0. Exit                                                   \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

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
            setcolor(INFO_COLOR);
            cout << "\n=== Generating Reports ===\n";
            db.displayAllStudents();
            db.displayAllCourses();
            db.displayAllFaculty();
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        case 7: 
            algorithmicEfficiencyMenu();
            break;
        case 0:
            setcolor(INFO_COLOR);
            cout << "\nExiting...\n";
            setcolor(MENU_OPTION_COLOR);
            break;
        default:
            setcolor(ERROR_COLOR);
            cout << "\n Invalid choice! Please try again.\n";
            setcolor(MENU_OPTION_COLOR);
        }
    } while (choice != 0);
}

void algorithmicEfficiencyMenu()
{
    int choice;
    AlgorithmicEfficiency analyzer;

    do
    {
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "          ALGORITHMIC EFFICIENCY ANALYSIS MENU              \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Generate Full Efficiency Report                        \n";
        cout << "  2. Analyze Consistency Checker                            \n";
        cout << "  3. Analyze Database Operations                            \n";
        cout << "  4. Analyze Induction Module                               \n";
        cout << "  5. Analyze Logic Engine                                   \n";
        cout << "  6. Analyze Set Operations                                 \n";
        cout << "  7. Analyze Relations Module                               \n";
        cout << "  8. View Optimization Summary                              \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
            setcolor(INFO_COLOR);
            cout << "\nGenerating comprehensive algorithmic efficiency report...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.generateFullReport();
            pauseScreen();
            break;
        case 2:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Consistency Checker module...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeConsistencyChecker();
            pauseScreen();
            break;
        case 3:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Database operations...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeDatabase();
            pauseScreen();
            break;
        case 4:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Induction Module...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeInductionModule();
            pauseScreen();
            break;
        case 5:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Logic Engine...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeLogicEngine();
            pauseScreen();
            break;
        case 6:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Set Operations...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeSetOperations();
            pauseScreen();
            break;
        case 7:
            setcolor(INFO_COLOR);
            cout << "\nAnalyzing Relations Module...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.analyzeRelationsModule();
            pauseScreen();
            break;
        case 8:
            setcolor(INFO_COLOR);
            cout << "\nGenerating optimization summary...\n";
            setcolor(MENU_OPTION_COLOR);
            analyzer.displaySummary();
            pauseScreen();
            break;
        case 0:
            break;
        default:
            setcolor(ERROR_COLOR);
            cout << "\n Invalid choice!\n";
            setcolor(MENU_OPTION_COLOR);
        }
    } while (choice != 0);
}

void dataManagementMenu()
{
    int choice;
    do
    {
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "                  DATA MANAGEMENT MENU                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Student Management                                     \n";
        cout << "  2. Course Management                                      \n";
        cout << "  3. Faculty Management                                     \n";
        cout << "  4. Enrollment Management                                  \n";
        cout << "  5. Load Data from Files                                   \n";
        cout << "  6. Save Data to Files                                     \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

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
            setcolor(INFO_COLOR);
            cout << "\nLoading data from file...\n";
            db.loadFromFile("university_data.txt");
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        case 6:
            setcolor(INFO_COLOR);
            cout << "\nSaving data to file...\n";
            db.saveToFile("university_data.txt");
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        case 0:
            break;
        default:
            setcolor(ERROR_COLOR);
            cout << "\n Invalid choice!\n";
            setcolor(MENU_OPTION_COLOR);
        }
    } while (choice != 0);
}

void studentMenu()
{
    int choice;
    do
    {
        setcolor(MENU_TITLE_COLOR);
        cout << "\n=== STUDENT MANAGEMENT ===\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "1. Add New Student\n";
        cout << "2. View Student Details\n";
        cout << "3. View All Students\n";
        cout << "4. Add Completed Course\n";
        cout << "5. Check Available Courses\n";
        cout << "0. Back\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
        {
            string id, name, dept;
            int year;
            setcolor(INFO_COLOR);
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
            setcolor(SUCCESS_COLOR);
            cout << " Student added successfully!\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            setcolor(INFO_COLOR);
            cout << "Enter Student ID: ";
            getline(cin, id);

            Student* s = db.getStudent(id);
            if (s)
            {
                s->display();
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Student not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
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
            setcolor(INFO_COLOR);
            cout << "Enter Student ID: ";
            getline(cin, studentId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            Student* s = db.getStudent(studentId);
            if (s)
            {
                s->addCompletedCourse(courseId);
                setcolor(SUCCESS_COLOR);
                cout << " Course added to completed courses!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Student not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 5:
        {
            string studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            vector<string> available = db.getAvailableCourses(studentId);
            setcolor(INFO_COLOR);
            cout << "\nAvailable Courses for Student " << studentId << ":\n";
            for (const string& c : available)
            {
                cout << "  - " << c << endl;
            }
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_TITLE_COLOR);
        cout << "\n=== COURSE MANAGEMENT ===\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "1. Add New Course\n";
        cout << "2. View Course Details\n";
        cout << "3. View All Courses\n";
        cout << "4. Add Prerequisite\n";
        cout << "5. View Course Prerequisites (Transitive)\n";
        cout << "6. Generate Valid Course Sequence\n";
        cout << "0. Back\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
        {
            string id, name;
            int credits;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, id);
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Credits: ";
            cin >> credits;
            cin.ignore();

            Courses c(id, name, credits);
            db.addCourse(c);
            setcolor(SUCCESS_COLOR);
            cout << " Course added successfully!\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, id);

            Courses* c = db.getCourse(id);
            if (c)
            {
                c->display();
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Course not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
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
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Prerequisite Course ID: ";
            getline(cin, prereqId);

            Courses* c = db.getCourse(courseId);
            if (c)
            {
                c->addPrerequisite(prereqId);
                db.buildPrerequisiteGraph();
                setcolor(SUCCESS_COLOR);
                cout << " Prerequisite added!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Course not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 5:
        {
            string courseId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            set<string> allPrereqs = db.getAllPrerequisites(courseId);
            setcolor(INFO_COLOR);
            cout << "\nAll Prerequisites (including indirect) for " << courseId << ":\n";
            for (const string& p : allPrereqs)
            {
                cout << "  - " << p << endl;
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 6:
        {
            vector<string> sequence = db.getValidCourseSequence();
            setcolor(INFO_COLOR);
            cout << "\nValid Course Sequence (Topological Order):\n";
            for (size_t i = 0; i < sequence.size(); i++)
            {
                cout << (i + 1) << ". " << sequence[i] << endl;
            }
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_TITLE_COLOR);
        cout << "\n=== FACULTY MANAGEMENT ===\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "1. Add New Faculty\n";
        cout << "2. View Faculty Details\n";
        cout << "3. View All Faculty\n";
        cout << "4. Assign Course to Faculty\n";
        cout << "0. Back\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
        {
            string id, name, dept;
            setcolor(INFO_COLOR);
            cout << "Enter Faculty ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Department: ";
            getline(cin, dept);

            Faculty f(id, name, dept);
            db.addFaculty(f);
            setcolor(SUCCESS_COLOR);
            cout << " Faculty added successfully!\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string id;
            setcolor(INFO_COLOR);
            cout << "Enter Faculty ID: ";
            getline(cin, id);

            Faculty* f = db.getFaculty(id);
            if (f)
            {
                f->display();
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Faculty not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
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
            setcolor(INFO_COLOR);
            cout << "Enter Faculty ID: ";
            getline(cin, facultyId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            Faculty* f = db.getFaculty(facultyId);
            if (f)
            {
                f->assignCourse(courseId);
                setcolor(SUCCESS_COLOR);
                cout << " Course assigned to faculty!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Faculty not found!\n";
            }
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_TITLE_COLOR);
        cout << "\n=== ENROLLMENT MANAGEMENT ===\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "1. Enroll Student in Course\n";
        cout << "2. View Student's Courses\n";
        cout << "3. View Course's Students\n";
        cout << "4. Check Enrollment Eligibility\n";
        cout << "0. Back\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
        {
            string studentId, courseId, timeSlotId, semesterId;
            setcolor(INFO_COLOR);
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
            setcolor(SUCCESS_COLOR);
            cout << " Enrollment added!\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            vector<string> courses = db.getStudentCourses(studentId);
            setcolor(INFO_COLOR);
            cout << "\nCourses for Student " << studentId << ":\n";
            for (const string& c : courses)
            {
                cout << "  - " << c << endl;
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 3:
        {
            string courseId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            vector<string> students = db.getEnrolledStudents(courseId);
            setcolor(INFO_COLOR);
            cout << "\nStudents enrolled in " << courseId << ":\n";
            for (const string& s : students)
            {
                cout << "  - " << s << endl;
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 4:
        {
            string studentId, courseId;
            setcolor(INFO_COLOR);
            cout << "Enter Student ID: ";
            getline(cin, studentId);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            if (db.canEnroll(studentId, courseId))
            {
                setcolor(SUCCESS_COLOR);
                cout << " Student CAN enroll in this course!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << " Student CANNOT enroll - prerequisites not met!\n";
            }
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "              CONSISTENCY & VERIFICATION MENU               \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Check Missing Prerequisites                            \n";
        cout << "  2. Detect Circular Prerequisites                          \n";
        cout << "  3. Validate Student Schedule Conflicts                    \n";
        cout << "  4. Check Room Double Booking                              \n";
        cout << "  5. Check Student Overload                                 \n";
        cout << "  6. Run All Consistency Checks                             \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        ConsistencyChecker checker;

        switch (choice)
        {
        case 1:
        {
            setcolor(INFO_COLOR);
            cout << "\n=== Checking Missing Prerequisites ===\n";
            // Build data structures for check
            map<string, vector<string>> prereqs;
            map<string, set<string>> studentCourses;

            // This is a simplified example - you'd need to populate these from db
            cout << " Feature requires additional data setup\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            setcolor(INFO_COLOR);
            cout << "\n=== Detecting Circular Prerequisites ===\n";
            if (db.hasCircularDependency())
            {
                setcolor(ERROR_COLOR);
                cout << " CIRCULAR DEPENDENCY DETECTED!\n";
                cout << "This is a critical error that must be fixed.\n";
            }
            else
            {
                setcolor(SUCCESS_COLOR);
                cout << " No circular dependencies found.\n";
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 6:
        {
            setcolor(MENU_BORDER_COLOR);
            cout << "\n==============================================================\n";
            setcolor(MENU_TITLE_COLOR);
            cout << "              RUNNING ALL CONSISTENCY CHECKS                \n";
            setcolor(MENU_BORDER_COLOR);
            cout << "==============================================================\n\n";
            setcolor(MENU_OPTION_COLOR);

            cout << "1. Circular Dependency Check: ";
            if (db.hasCircularDependency())
            {
                setcolor(ERROR_COLOR);
                cout << " FAILED\n";
            }
            else
            {
                setcolor(SUCCESS_COLOR);
                cout << " PASSED\n";
            }

            setcolor(SUCCESS_COLOR);
            cout << "\n All checks completed!\n";
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 0:
            break;
        default:
            setcolor(ERROR_COLOR);
            cout << "\n Invalid choice!\n";
            setcolor(MENU_OPTION_COLOR);
        }
    } while (choice != 0);
}

void inductionMenu()
{
    int choice;
    do
    {
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "            INDUCTION & PROOF GENERATION MENU               \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Verify Prerequisite Chain (Simple Induction)           \n";
        cout << "  2. Generate Induction Proof                               \n";
        cout << "  3. Verify with Strong Induction                           \n";
        cout << "  4. Generate Strong Induction Proof                        \n";
        cout << "  5. Display Prerequisite Chain Tree                        \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        InductionModule inductionModule(&db);

        switch (choice)
        {
        case 1:
        {
            string courseId, studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            if (inductionModule.verifyPrerequisiteChain(courseId, studentId))
            {
                setcolor(SUCCESS_COLOR);
                cout << "\n All prerequisites verified!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << "\n Prerequisites not satisfied!\n";
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string courseId, studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            InductionModule::Proof proof = inductionModule.generateInductionProof(courseId, studentId);
            proof.display();
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 3:
        {
            string courseId, studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            if (inductionModule.verifyWithStrongInduction(courseId, studentId))
            {
                setcolor(SUCCESS_COLOR);
                cout << "\n Strong induction verification PASSED!\n";
            }
            else
            {
                setcolor(ERROR_COLOR);
                cout << "\n Strong induction verification FAILED!\n";
            }
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 4:
        {
            string courseId, studentId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            InductionModule::Proof proof = inductionModule.generateStrongInductionProof(courseId, studentId);
            proof.display();
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 5:
        {
            string courseId;
            setcolor(INFO_COLOR);
            cout << "Enter Course ID: ";
            getline(cin, courseId);

            setcolor(INFO_COLOR);
            cout << "\n=== Prerequisite Chain Tree ===\n";
            inductionModule.displayPrerequisiteChain(courseId);
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "              LOGIC & INFERENCE ENGINE MENU                 \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Add Logical Rule                                       \n";
        cout << "  2. Add Fact                                               \n";
        cout << "  3. Display All Rules                                      \n";
        cout << "  4. Display All Facts                                      \n";
        cout << "  5. Perform Inference (Modus Ponens, etc.)                 \n";
        cout << "  6. Detect Conflicts                                       \n";
        cout << "  7. Generate Truth Table                                   \n";
        cout << "  8. Load Rules from File                                   \n";
        cout << "  9. Save Rules to File                                     \n";
        cout << "  10. Display Statistics                                    \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

        switch (choice)
        {
        case 1:
        {
            string condition, consequence, ruleType;
            setcolor(INFO_COLOR);
            cout << "Enter condition (IF part): ";
            getline(cin, condition);
            cout << "Enter consequence (THEN part): ";
            getline(cin, consequence);
            cout << "Enter rule type (IMPLIES/AND/OR/NOT): ";
            getline(cin, ruleType);

            string ruleId = logicEngine.addRule(condition, consequence, ruleType);
            setcolor(SUCCESS_COLOR);
            cout << " Rule added with ID: " << ruleId << endl;
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 2:
        {
            string statement;
            char truthChar;
            setcolor(INFO_COLOR);
            cout << "Enter statement: ";
            getline(cin, statement);
            cout << "Is it true? (y/n): ";
            cin >> truthChar;
            cin.ignore();

            bool truthValue = (truthChar == 'y' || truthChar == 'Y');
            string factId = logicEngine.addFact(statement, truthValue);
            setcolor(SUCCESS_COLOR);
            cout << " Fact added with ID: " << factId << endl;
            setcolor(MENU_OPTION_COLOR);
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
            setcolor(INFO_COLOR);
            cout << "Enter logical expression: ";
            getline(cin, expression);

            vector<string> vars;
            logicEngine.displayTruthTable(expression, vars);
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 8:
        {
            string filename;
            setcolor(INFO_COLOR);
            cout << "Enter filename (default: logic_rules.txt): ";
            getline(cin, filename);
            if (filename.empty()) filename = "logic_rules.txt";
            logicEngine.loadRules(filename);
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        case 9:
        {
            string filename;
            setcolor(INFO_COLOR);
            cout << "Enter filename (default: logic_rules.txt): ";
            getline(cin, filename);
            if (filename.empty()) filename = "logic_rules.txt";
            logicEngine.saveRules(filename);
            setcolor(MENU_OPTION_COLOR);
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
        setcolor(MENU_BORDER_COLOR);
        cout << "\n==============================================================\n";
        setcolor(MENU_TITLE_COLOR);
        cout << "            DISCRETE MATHEMATICS MODULES MENU               \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_OPTION_COLOR);
        cout << "  1. Set Operations Demonstration                           \n";
        cout << "  2. Relations Demonstration                                \n";
        cout << "  3. Functions Demonstration                                \n";
        cout << "  4. Student Group Combinations                             \n";
        cout << "  0. Back to Main Menu                                      \n";
        setcolor(MENU_BORDER_COLOR);
        cout << "==============================================================\n";
        setcolor(MENU_HIGHLIGHT_COLOR);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        setcolor(MENU_OPTION_COLOR);

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

            setcolor(MENU_TITLE_COLOR);
            cout << "\n=== Student Group Combinations ===\n";
            setcolor(MENU_OPTION_COLOR);
            cout << "1. Generate all possible groups\n";
            cout << "2. Form project groups (sequential)\n";
            setcolor(MENU_HIGHLIGHT_COLOR);
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();
            setcolor(MENU_OPTION_COLOR);

            if (subChoice == 1)
            {
                int groupSize, numStudents;
                setcolor(INFO_COLOR);
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
                setcolor(INFO_COLOR);
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
            setcolor(MENU_OPTION_COLOR);
            pauseScreen();
            break;
        }
        }
    } while (choice != 0);
}