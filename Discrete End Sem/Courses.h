#pragma once 
#ifndef COURSES_H 
#define COURSES_H 
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 
class Courses { 
private: 
	string id;
	string name;
	int credits;
	vector<string> prerequisites; 
public: 
	Courses() {} 
	Courses(string id, string name, int credits); 
	string getId() const; 
	string getName() const; 
	int getCredits() const; 
	void addPrerequisite(string prereqId); 
	const vector<string>& getPrerequisites() const; 
	void display() const; 
}; 
#endif