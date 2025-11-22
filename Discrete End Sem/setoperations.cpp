#include "SetOperations.h"

set<string> SetOperations::unionSets(const set<string>& setA, const set<string>& setB)
{
    set<string> result = setA;
    for (const string& element : setB)
    {
        result.insert(element);
    }
    return result;
}

set<string> SetOperations::intersectionSets(const set<string>& setA, const set<string>& setB)
{
    set<string> result;
    for (const string& element : setA)
    {
        if (setB.find(element) != setB.end())
        {
            result.insert(element);
        }
    }
    return result;
}

set<string> SetOperations::differenceSets(const set<string>& setA, const set<string>& setB)
{
    set<string> result;
    for (const string& element : setA)
    {
        if (setB.find(element) == setB.end())
        {
            result.insert(element);
        }
    }
    return result;
}

set<string> SetOperations::symmetricDifference(const set<string>& setA, const set<string>& setB)
{
    set<string> diffAB = differenceSets(setA, setB);
    set<string> diffBA = differenceSets(setB, setA);
    return unionSets(diffAB, diffBA);
}

bool SetOperations::isSubset(const set<string>& setA, const set<string>& setB)
{
    for (const string& element : setA)
    {
        if (setB.find(element) == setB.end())
        {
            return false;
        }
    }
    return true;
}

bool SetOperations::isProperSubset(const set<string>& setA, const set<string>& setB)
{
    return isSubset(setA, setB) && setA.size() < setB.size();
}

bool SetOperations::isSuperset(const set<string>& setA, const set<string>& setB)
{
    return isSubset(setB, setA);
}

vector<set<string>> SetOperations::powerSet(const set<string>& inputSet)
{
    vector<string> elements(inputSet.begin(), inputSet.end());
    int n = elements.size();
    int powerSetSize = 1 << n;

    vector<set<string>> result;

    for (int i = 0; i < powerSetSize; i++)
    {
        set<string> subset;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                subset.insert(elements[j]);
            }
        }
        result.push_back(subset);
    }

    return result;
}

set<pair<string, string>> SetOperations::cartesianProduct(const set<string>& setA, const set<string>& setB)
{
    set<pair<string, string>> result;
    for (const string& a : setA)
    {
        for (const string& b : setB)
        {
            result.insert(make_pair(a, b));
        }
    }
    return result;
}

int SetOperations::cardinality(const set<string>& inputSet)
{
    return inputSet.size();
}

bool SetOperations::areEqual(const set<string>& setA, const set<string>& setB)
{
    return setA == setB;
}

bool SetOperations::areDisjoint(const set<string>& setA, const set<string>& setB)
{
    return intersectionSets(setA, setB).empty();
}

void SetOperations::displaySet(const set<string>& inputSet, const string& setName)
{
    cout << setName << " = { ";
    bool first = true;
    for (const string& element : inputSet)
    {
        if (!first)
        {
            cout << ", ";
        }
        cout << element;
        first = false;
    }
    cout << " }" << endl;
    cout << "Cardinality: |" << setName << "| = " << inputSet.size() << endl;
}

void SetOperations::displayPowerSet(const vector<set<string>>& pSet, const string& setName)
{
    cout << "\n" << setName << " (Size: " << pSet.size() << "):" << endl;
    int index = 0;
    for (const set<string>& subset : pSet)
    {
        cout << "  Subset " << index++ << ": { ";
        bool first = true;
        for (const string& element : subset)
        {
            if (!first)
            {
                cout << ", ";
            }
            cout << element;
            first = false;
        }
        cout << " }" << endl;
    }
}

set<string> SetOperations::vectorToSet(const vector<string>& vec)
{
    return set<string>(vec.begin(), vec.end());
}

vector<string> SetOperations::setToVector(const set<string>& inputSet)
{
    return vector<string>(inputSet.begin(), inputSet.end());
}

void SetOperations::demonstrateSetOperations()
{
    cout << "\n========== SET OPERATIONS MODULE DEMONSTRATION ==========\n";

    set<string> cs101Students = { "S001", "S002", "S003", "S004", "S005" };
    set<string> math101Students = { "S003", "S004", "S005", "S006", "S007" };
    set<string> physics101Students = { "S001", "S005", "S008", "S009" };

    cout << "\n--- Original Sets ---\n";
    displaySet(cs101Students, "CS101 Students");
    displaySet(math101Students, "Math101 Students");
    displaySet(physics101Students, "Physics101 Students");

    cout << "\n--- Union Operation ---\n";
    set<string> allStudents = unionSets(cs101Students, math101Students);
    displaySet(allStudents, "CS101 ∪ Math101");

    cout << "\n--- Intersection Operation ---\n";
    set<string> commonStudents = intersectionSets(cs101Students, math101Students);
    displaySet(commonStudents, "CS101 ∩ Math101");

    cout << "\n--- Difference Operation ---\n";
    set<string> onlyCS = differenceSets(cs101Students, math101Students);
    displaySet(onlyCS, "CS101 - Math101");

    cout << "\n--- Symmetric Difference ---\n";
    set<string> symDiff = symmetricDifference(cs101Students, math101Students);
    displaySet(symDiff, "CS101 Δ Math101");

    cout << "\n--- Subset Relations ---\n";
    set<string> smallSet = { "S001", "S002" };
    cout << "Is {S001, S002} ⊆ CS101? " << (isSubset(smallSet, cs101Students) ? "Yes" : "No") << endl;
    cout << "Is CS101 ⊆ Math101? " << (isSubset(cs101Students, math101Students) ? "Yes" : "No") << endl;

    cout << "\n--- Disjoint Check ---\n";
    set<string> lab1 = { "S001", "S002" };
    set<string> lab2 = { "S003", "S004" };
    cout << "Are Lab1 and Lab2 disjoint? " << (areDisjoint(lab1, lab2) ? "Yes" : "No") << endl;

    cout << "\n--- Power Set ---\n";
    set<string> courses = { "CS101", "Math101" };
    vector<set<string>> pSet = powerSet(courses);
    displayPowerSet(pSet, "Power Set of {CS101, Math101}");

    cout << "\n--- Cartesian Product ---\n";
    set<string> students = { "S001", "S002" };
    set<string> coursesSmall = { "CS101", "Math101" };
    set<pair<string, string>> cartesian = cartesianProduct(students, coursesSmall);
    cout << "Students × Courses = { ";
    bool first = true;
    for (const auto& pair : cartesian)
    {
        if (!first)
        {
            cout << ", ";
        }
        cout << "(" << pair.first << ", " << pair.second << ")";
        first = false;
    }
    cout << " }" << endl;

    cout << "\n=========================================================\n";
}