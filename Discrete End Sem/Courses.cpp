#include "Courses.h"

Courses::Courses(string id, string name, int credits)
{
    this->id = id;
    this->name = name;
    this->credits = credits;
}

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
    for (size_t i = 0; i < prerequisites.size(); ++i)
        cout << prerequisites[i] << " ";
    cout << endl;
}
