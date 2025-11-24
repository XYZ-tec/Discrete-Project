#pragma once
#ifndef COURSE_SCHEDULING_H
#define COURSE_SCHEDULING_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class CourseScheduling
{
private:
    map<string, vector<string>> prereq;

    bool canTake(string course, vector<string>& taken);
    void generate(vector<string>& current, vector<string>& allCourses,
        vector<vector<string>>& result, vector<bool>& used);

public:
    CourseScheduling();

    void addCourse(string course, vector<string> prerequisites);
    void addPrerequisite(string course, string pre);
    void removePrerequisite(string course, string pre);
    void removeCourse(string course);

    bool isCourseAvailable(string course);
    vector<string> getAllCourses();
    vector<string> getPrerequisites(string course);

    bool checkPrerequisitesMet(string course, vector<string> completed);
    int countPrerequisites(string course);

    void printCourseInfo(string course);
    void printAllCourses();

    vector<vector<string>> generateSchedules();
};

#endif

