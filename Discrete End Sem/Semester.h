#pragma once
#ifndef SEMESTER_H
#define SEMESTER_H
#include <iostream>
#include <string>
using namespace std;
class Semester 
{
private:
    string id;
    string name;  // e.g Fall 2023
    string startDate;
    string endDate;
public:
	Semester() {}
    Semester(string id, string name, string start, string end);
    string getId() const;
    string getName() const;
    string getStartDate() const;
    string getEndDate() const;
    void display() const;
};
#endif