#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Student
{
private:
    string id;
    string name;
    string department;
    int year;
    vector<string> completedCourses;  // Set of completed courses (discrete: set)
public:
    Student(string id, string name, string dept, int year);
    string getId() const;
    string getName() const;
    string getDepartment() const;
    int getYear() const;
    void addCompletedCourse(string courseId);
    bool hasCompletedCourse(string courseId) const;
    void display() const;
};

#endif