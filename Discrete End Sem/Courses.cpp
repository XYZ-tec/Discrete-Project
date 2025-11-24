#include "Courses.h"
Courses::Courses() {}
Courses::Courses(string id, string name, int credits)
    : id(id), name(name), credits(credits) {
}
string Courses::getId() const { return id; }
string Courses::getName() const { return name; }
int Courses::getCredits() const { return credits; }
void Courses::setId(string x) { id = x; }
void Courses::setName(string x) { name = x; }
void Courses::setCredits(int x) { credits = x; }
void Courses::addPrerequisite(string prereqId)
{
    prerequisites.push_back(prereqId);
}
void Courses::removePrerequisite(string prereqId)
{
    vector<string> temp;
    for (auto& p : prerequisites)
        if (p != prereqId)
            temp.push_back(p);
    prerequisites = temp;
}
bool Courses::hasPrerequisite(string prereqId) const
{
    for (auto& p : prerequisites)
        if (p == prereqId)
            return true;
    return false;
}
void Courses::clearPrerequisites()
{
    prerequisites.clear();
}
int Courses::totalPrerequisiteCount() const
{
    return prerequisites.size();
}
const vector<string>& Courses::getPrerequisites() const
{
    return prerequisites;
}
void Courses::addEquivalentCourse(string cid)
{
    equivalentCourses.insert(cid);
}
bool Courses::isEquivalentTo(string cid) const
{
    return equivalentCourses.find(cid) != equivalentCourses.end();
}
void Courses::clearEquivalentCourses()
{
    equivalentCourses.clear();
}
const set<string>& Courses::getEquivalentCourses() const
{
    return equivalentCourses;
}
void Courses::setSemester(string semester, int value)
{
    semesterOffered[semester] = value;
}
bool Courses::isOfferedInSemester(string semester) const
{
    return semesterOffered.find(semester) != semesterOffered.end();
}
void Courses::removeSemester(string semester)
{
    semesterOffered.erase(semester);
}
int Courses::getSemesterValue(string semester) const
{
    auto it = semesterOffered.find(semester);
    if (it != semesterOffered.end())
        return it->second;
    return -1;
}
bool Courses::canTake(const set<string>& completed) const
{
    for (auto& p : prerequisites)
        if (completed.find(p) == completed.end())
            return false;
    return true;
}
bool Courses::matchesName(string x) const
{
    return name.find(x) != string::npos;
}
int Courses::compareCredits(const Courses& other) const
{
    if (credits > other.credits) return 1;
    if (credits < other.credits) return -1;
    return 0;
}
vector<vector<string>> Courses::generateValidOrders() const
{
    vector<vector<string>> result;
    vector<string> order;

    for (auto& p : prerequisites)
        order.push_back(p);

    order.push_back(id);
    result.push_back(order);

    return result;
}

bool Courses::isPrerequisiteChainValid(const map<string, Courses>& all) const
{
    set<string> visited;
    vector<string> stack = prerequisites;

    while (!stack.empty()) {
        string current = stack.back();
        stack.pop_back();

        if (current == id)
            return false;

        if (visited.find(current) != visited.end())
            continue;

        visited.insert(current);

        auto it = all.find(current);
        if (it != all.end())
            for (auto& p : it->second.getPrerequisites())
                stack.push_back(p);
    }

    return true;
}

void Courses::display() const
{
    cout << "Course ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Credits: " << credits << endl;

    cout << "Prerequisites: ";
    if (prerequisites.empty()) cout << "None";
    else for (auto& p : prerequisites) cout << p << " ";
    cout << endl;

    cout << "Equivalent Courses: ";
    if (equivalentCourses.empty()) cout << "None";
    else for (auto& e : equivalentCourses) cout << e << " ";
    cout << endl;

    cout << "Semesters: ";
    if (semesterOffered.empty()) cout << "None";
    else for (auto& s : semesterOffered) cout << s.first << ":" << s.second << " ";
    cout << endl;
}
