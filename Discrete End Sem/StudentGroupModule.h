#pragma once
#ifndef STUDENTGROUPMODULE_H
#define STUDENTGROUPMODULE_H
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
using namespace std;

class GroupGenerator {
public:
    struct Group {
        int groupId;
        vector<string> memberIds;
        string type;  // "Project", "Lab", "Elective"

        void display() const
        {
            cout << "Group " << groupId << " [" << type << "]: ";
            for (size_t i = 0; i < memberIds.size(); i++)
            {
                cout << memberIds[i];
                if (i < memberIds.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    };

    struct LabSession {
        string labId;
        int capacity;
        set<string> assignedStudents;  

        void display() const {
            cout << "Lab: " << labId << " | Capacity: " << capacity
                << " | Enrolled: " << assignedStudents.size() << endl;
            cout << "  Students: ";
            for (const string& sid : assignedStudents) {
                cout << sid << " ";
            }
            cout << endl;
        }
    };

private:
    int nextGroupId;
    vector<LabSession> labSessions;

public:
    GroupGenerator() : nextGroupId(1) {}

    // Generate all possible combinations C(n,r)
    vector<Group> generateAllCombinations( vector<string> studentIds, int groupSize );

    // Form project groups
    vector<Group> formProjectGroups( vector<string> studentIds, int groupSize );

    void addLabSession(string labId, int capacity);

    bool assignToLabSessions(vector<string> studentIds);
    
    void displayLabSessions();

    // Get students who selected an elective 
    set<string> getStudentsInElective( map<string, set<string>>& electiveSelections, string electiveName );

    // Find common students in multiple electives (INTERSECTION)
    set<string> findCommonStudents( set<string>& elective1Students, set<string>& elective2Students );

    // Find all students in either elective (UNION)
    set<string> findAllStudents( set<string>& elective1Students, set<string>& elective2Students );

    // Calculate C(n, r) = n! / (r! * (n-r)!)
    int calculateCombinations(int n, int r);

    // Calculate total possible groups
    void displayCombinationStats(int numStudents, int groupSize);

    void displayGroups(vector<Group>& groups);

private:
    // Recursive helper for combinations
    void combineHelper(vector<string>& students, int groupSize, int start, vector<string>& current, vector<Group>& result);

    int factorial(int n);
};

#endif