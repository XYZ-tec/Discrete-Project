#include "Transcript.h"
Transcript::Transcript(string sId) : studentId(sId) {}

void Transcript::addGrade(string courseId, string grade)
{
    grades.push_back(make_pair(courseId, grade));
}

string Transcript::getStudentId() const 
{
    return studentId;
}

double Transcript::calculateGPA() const 
{
    if (grades.empty()) 
    {
        return 0.0;
    }

    double totalPoints = 0.0;
    int count = 0;

    for (const auto& gradeEntry : grades)
    {
        string grade = gradeEntry.second;
        double points = 0.0;

        // Convert letter grade to GPA points
        if (grade == "A" || grade == "A+")
        {
            points = 4.0;
        }
        else if (grade == "A-")
        {
            points = 3.67;
        }
        else if (grade == "B+")
        {
            points = 3.33;
        }
        else if (grade == "B") 
        {
            points = 3.0;
        }
        else if (grade == "B-") 
        {
            points = 2.67;
        }
        else if (grade == "C+")
        {
            points = 2.33;
        }
        else if (grade == "C") 
        {
            points = 2.0;
        }
        else if (grade == "C-")
        {
            points = 1.67;
        }
        else if (grade == "D+") 
        {
            points = 1.33;
        }
        else if (grade == "D") 
        {
            points = 1.0;
		}
        else if (grade == "F") 
        {
            points = 0.0;
        }

        totalPoints += points;
        count++;
    }

    return totalPoints / count;
}

void Transcript::display() const
{
    cout << "Transcript for Student ID: " << studentId << endl;
    cout << "Course Grades:" << endl;
    for (const auto& gradeEntry : grades)
    {
        cout << "  Course: " << gradeEntry.first << ", Grade: " << gradeEntry.second << endl;
    }
    cout << "GPA: " << calculateGPA() << endl;
}