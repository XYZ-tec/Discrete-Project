#include "Student.h"

Student::Student(string id, string name, string dept, int year): id(id), name(name), department(dept), year(year) {}

string Student::getId() const 
{
    return id;
}

string Student::getName() const 
{
    return name;
}

string Student::getDepartment() const 
{
    return department;
}

int Student::getYear() const 
{
    return year;
}

void Student::addCompletedCourse(string courseId) 
{
    completedCourses.push_back(courseId);
}

const vector<string>& Student::getCompletedCourses() const 
{
    return completedCourses;
}

bool Student::hasCompletedCourse(string courseId) const 
{
    for (const string& course : completedCourses) 
    {
        if (course == courseId) 
        {
            return true;
        }
    }
    return false;
}

void Student::display() const 
{
    cout << "Student ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Year: " << year << endl;
    cout << "Completed Courses: ";
    for (const string& course : completedCourses) 
    {
        cout << course << " ";
    }
    cout << endl;
}