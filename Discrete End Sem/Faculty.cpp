#include "Faculty.h"

Faculty::Faculty(string id, string name, string dept): id(id), name(name), department(dept) {}

string Faculty::getId() const
{
    return id;
}

string Faculty::getName() const 
{
    return name;
}

string Faculty::getDepartment() const
{
    return department;
}

void Faculty::assignCourse(string courseId) 
{
    assignedCourses.push_back(courseId);
}

const vector<string>& Faculty::getAssignedCourses() const 
{
    return assignedCourses;
}

void Faculty::display() const
{
    cout << "Faculty ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Assigned Courses: ";
    if (assignedCourses.empty()) 
    {
        cout << "None";
    }
    else 
    {
        for (const string& course : assignedCourses) 
        {
            cout << course << " ";
        }
    }
    cout << endl;
}