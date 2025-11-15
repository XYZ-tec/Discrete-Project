#pragma once
#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include<iostream>
#include <string>
#include <vector>
using namespace std;
class Department 
{
private:
    string id;
    string name;
    vector<string> studentIds;  // Set of student IDs in department

public:
    Department(string id, string name);
    string getId() const;
    string getName() const;
    void addStudent(string studentId);
    const vector<string>& getStudents() const;
    void display() const;
};

#endif