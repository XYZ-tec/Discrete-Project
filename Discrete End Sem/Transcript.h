#pragma once
#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H
#include<iostream>
#include <string>
#include <vector>
#include "Student.h"
using namespace std;
class Transcript 
{
private:
    string studentId;
    vector<pair<string, string>> grades;  // For Pairing The Course ID and Grade e.g A B and so on

public:
	Transcript() {}
    Transcript(string sId);
    void addGrade(string courseId, string grade);
    double calculateGPA() const; 
    void display() const;
};

#endif