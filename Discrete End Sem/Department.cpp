#include "Department.h"
Department::Department(string id, string name): id(id), name(name) {}

string Department::getId() const 
{
    return id;
}

string Department::getName() const
{
    return name;
}

void Department::addStudent(string studentId) 
{
    studentIds.push_back(studentId);
}

const vector<string>& Department::getStudents() const
{
    return studentIds;
}

void Department::display() const 
{
    cout << "Department ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Number of Students: " << studentIds.size() << endl;
    cout << "Student IDs: ";
    for (const string& sId : studentIds)
    {
        cout << sId << " ";
    }
    cout << endl;
}