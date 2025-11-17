#include "Semester.h"
Semester::Semester(string id, string name, string start, string end): id(id), name(name), startDate(start), endDate(end) {}

string Semester::getId() const 
{
    return id;
}

string Semester::getName() const 
{
    return name;
}

string Semester::getStartDate() const 
{
    return startDate;
}

string Semester::getEndDate() const 
{
    return endDate;
}

void Semester::display() const 
{
    cout << "Semester ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Duration: " << startDate << " to " << endDate << endl;
}