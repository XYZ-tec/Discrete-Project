#pragma once
#ifndef COURSES_H
#define COURSES_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;
class Courses
{
private:
    string id;
    string name;
    int credits;
    vector<string> prerequisites;
    map<string, int> semesterOffered;
    set<string> equivalentCourses;
public:
    Courses();
    Courses(string id, string name, int credits);
    string getId() const;
    string getName() const;
    int getCredits() const;
    void setId(string x);
    void setName(string x);
    void setCredits(int x);
    void addPrerequisite(string prereqId);
    void removePrerequisite(string prereqId);
    bool hasPrerequisite(string prereqId) const;
    void clearPrerequisites();
    int totalPrerequisiteCount() const;
    const vector<string>& getPrerequisites() const;
    void addEquivalentCourse(string cid);
    bool isEquivalentTo(string cid) const;
    void clearEquivalentCourses();
    const set<string>& getEquivalentCourses() const;
    void setSemester(string semester, int value);
    bool isOfferedInSemester(string semester) const;
    void removeSemester(string semester);
    int getSemesterValue(string semester) const;
    bool canTake(const set<string>& completed) const;
    bool matchesName(string x) const;
    int compareCredits(const Courses& other) const;
    vector<vector<string>> generateValidOrders() const;
    bool isPrerequisiteChainValid(const map<string, Courses>& all) const;
    void display() const;
};
#endif
