#pragma once
#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Faculty
{
private:
    string id;
    string name;
    string department;
    vector<string> assignedCourses;  // Set of assigned course IDs

public:
    Faculty() {}
    Faculty(string id, string name, string dept);
    string getId() const;
    string getName() const;
    string getDepartment() const;
    void assignCourse(string courseId);
    const vector<string>& getAssignedCourses() const;
    void display() const;
};

#endif