#include "Courses.h"
Courses::Courses(string id, string name, int credits): id(id), name(name), credits(credits) {}

string Courses::getId() const 
{
    return id;
}

string Courses::getName() const 
{
    return name;
}

int Courses::getCredits() const
{
    return credits;
}

void Courses::addPrerequisite(string prereqId)
{
    prerequisites.push_back(prereqId);
}

const vector<string>& Courses::getPrerequisites() const 
{
    return prerequisites;
}

void Courses::display() const 
{
    cout << "Course ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Credits: " << credits << endl;
    cout << "Prerequisites: ";
    if (prerequisites.empty()) 
    {
        cout << "None";
    }
    else 
    {
        for (const string& prereq : prerequisites) 
        {
            cout << prereq << " ";
        }
    }
    cout << endl;
}