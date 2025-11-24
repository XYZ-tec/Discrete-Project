#include "CourseScheduling.h"
#include <iostream>

CourseScheduling::CourseScheduling() {}

bool CourseScheduling::canTake(string course, vector<string>& taken)
{
    if (prereq.find(course) == prereq.end())
        return true;

    vector<string> req = prereq[course];

    for (int i = 0; i < req.size(); i++)
    {
        bool ok = false;
        for (int j = 0; j < taken.size(); j++)
        {
            if (taken[j] == req[i])
            {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

void CourseScheduling::addCourse(string course, vector<string> prerequisites)
{
    prereq[course] = prerequisites;
}

void CourseScheduling::addPrerequisite(string course, string pre)
{
    prereq[course].push_back(pre);
}

void CourseScheduling::removePrerequisite(string course, string pre)
{
    vector<string> list = prereq[course];
    vector<string> newList;

    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] != pre)
            newList.push_back(list[i]);
    }
    prereq[course] = newList;
}

void CourseScheduling::removeCourse(string course)
{
    prereq.erase(course);

    for (auto& p : prereq)
    {
        vector<string> newList;
        vector<string> oldList = p.second;

        for (int i = 0; i < oldList.size(); i++)
        {
            if (oldList[i] != course)
                newList.push_back(oldList[i]);
        }
        p.second = newList;
    }
}

bool CourseScheduling::isCourseAvailable(string course)
{
    return prereq.find(course) != prereq.end();
}

vector<string> CourseScheduling::getAllCourses()
{
    vector<string> list;

    for (auto& c : prereq)
        list.push_back(c.first);

    return list;
}

vector<string> CourseScheduling::getPrerequisites(string course)
{
    if (prereq.find(course) == prereq.end())
        return {};

    return prereq[course];
}

bool CourseScheduling::checkPrerequisitesMet(string course, vector<string> completed)
{
    if (prereq.find(course) == prereq.end())
        return true;

    vector<string> req = prereq[course];

    for (int i = 0; i < req.size(); i++)
    {
        bool met = false;
        for (int j = 0; j < completed.size(); j++)
        {
            if (completed[j] == req[i])
            {
                met = true;
                break;
            }
        }
        if (!met) return false;
    }
    return true;
}

int CourseScheduling::countPrerequisites(string course)
{
    if (prereq.find(course) == prereq.end())
        return 0;

    return prereq[course].size();
}

void CourseScheduling::printCourseInfo(string course)
{
    if (prereq.find(course) == prereq.end())
    {
        cout << "Course not found\n";
        return;
    }

    cout << "Course: " << course << endl;

    vector<string> req = prereq[course];
    cout << "Prerequisites: ";
    for (int i = 0; i < req.size(); i++)
        cout << req[i] << " ";

    cout << endl;
}

void CourseScheduling::printAllCourses()
{
    cout << "All Courses:\n";

    for (auto& c : prereq)
        cout << c.first << endl;
}

void CourseScheduling::generate(vector<string>& current,
    vector<string>& allCourses,
    vector<vector<string>>& result,
    vector<bool>& used)
{
    if (current.size() == allCourses.size())
    {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < allCourses.size(); i++)
    {
        if (!used[i])
        {
            if (canTake(allCourses[i], current))
            {
                used[i] = true;
                current.push_back(allCourses[i]);

                generate(current, allCourses, result, used);

                current.pop_back();
                used[i] = false;
            }
        }
    }
}

vector<vector<string>> CourseScheduling::generateSchedules()
{
    vector<string> allCourses;
    for (auto& c : prereq)
        allCourses.push_back(c.first);

    vector<vector<string>> result;
    vector<string> current;
    vector<bool> used(allCourses.size(), false);

    generate(current, allCourses, result, used);
    return result;
}
