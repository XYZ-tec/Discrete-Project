#include "StudentGroupModule.h"
#include "setoperationsModule.h"
vector<GroupGenerator::Group> GroupGenerator::generateAllCombinations(vector<string> studentIds,int groupSize) {
    vector<Group> result;
    vector<string> current;
    combineHelper(studentIds, groupSize, 0, current, result);
    return result;
}

void GroupGenerator::combineHelper( vector<string>& students, int groupSize, int start, vector<string>& current, vector<Group>& result) {
    if (current.size() == groupSize)
    {
        Group g;
        g.groupId = nextGroupId++;
        g.memberIds = current;
        g.type = "Project";
        result.push_back(g);
        return;
    }
    for (int i = start; i < students.size(); i++) 
    {
        current.push_back(students[i]);
        combineHelper(students, groupSize, i + 1, current, result);
        current.pop_back();
    }
}

vector<GroupGenerator::Group> GroupGenerator::formProjectGroups( vector<string> studentIds, int groupSize) {
    vector<Group> result;
    for (int i = 0; i < studentIds.size(); i += groupSize)
    {
        Group g;
        g.groupId = nextGroupId++;
        g.type = "Project";
        for (int j = i; j < i + groupSize && j < studentIds.size(); j++)
        {
            g.memberIds.push_back(studentIds[j]);
        }
        result.push_back(g);
    }
    return result;
}

void GroupGenerator::addLabSession(string labId, int capacity)
{ 
    LabSession lab; 
    lab.labId = labId; 
    lab.capacity = capacity; 
    labSessions.push_back(lab);
}

bool GroupGenerator::assignToLabSessions(vector<string> studentIds) {
    //  assign to first available lab
    for (const string& sid : studentIds) 
    {
        bool assigned = false;
        for (LabSession& lab : labSessions)
        {
            if (lab.assignedStudents.size() < lab.capacity) {
                lab.assignedStudents.insert(sid); 
                assigned = true;
                break;
            }
        }

        if (!assigned)
        {
            cout << "Error: Cannot assign " << sid << " - all labs full!\n";
            return false;
        }
    }

    return true;
}

void GroupGenerator::displayLabSessions()
{
    cout << "\n========== LAB SESSIONS ==========\n";
    for (const LabSession& lab : labSessions) {
        lab.display();
    }
    cout << endl;
}

set<string> GroupGenerator::getStudentsInElective( map<string, set<string>>& electiveSelections, string electiveName) {
    if (electiveSelections.find(electiveName) != electiveSelections.end()) 
    {
        return electiveSelections[electiveName];
    }
    return set<string>();  // Empty set
}

// SET INTERSECTION 
set<string> GroupGenerator::findCommonStudents(set<string>& elective1Students,set<string>& elective2Students)
{
    return SetOperations::intersectionSets(elective1Students, elective2Students);
}

// SET UNION 
set<string> GroupGenerator::findAllStudents( set<string>& elective1Students, set<string>& elective2Students )
{
    return SetOperations::unionSets(elective1Students, elective2Students);
}

int GroupGenerator::factorial(int n) 
{
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int GroupGenerator::calculateCombinations(int n, int r) 
{
    if (r > n) 
        return 0;
    // C(n,r) = n! / (r! * (n-r)!)
    return factorial(n) / (factorial(r) * factorial(n - r));
}

void GroupGenerator::displayCombinationStats(int numStudents, int groupSize) 
{
    int totalCombinations = calculateCombinations(numStudents, groupSize);

    cout << "\n========== COMBINATION STATISTICS ==========\n";
    cout << "Number of students (n): " << numStudents << endl;
    cout << "Group size (r): " << groupSize << endl;
    cout << "Formula: C(n,r) = n! / (r! * (n-r)!)" << endl;
    cout << "C(" << numStudents << "," << groupSize << ") = "
        << totalCombinations << " possible groups" << endl;
    cout << endl;
}

void GroupGenerator::displayGroups(vector<Group>& groups) 
{
    cout << "\n========== GROUPS ==========\n";
    cout << "Total Groups: " << groups.size() << "\n\n";

    for (auto& g : groups)
    {
        g.display();
    }
    cout << "============================\n";
}