#include "RelationsModule.h"

bool RelationsModule::isReflexive(const Relation& relation, const set<string>& domain)
{
    for (const string& element : domain)
    {
        if (relation.find(make_pair(element, element)) == relation.end())
        {
            return false;
        }
    }
    return true;
}

bool RelationsModule::isSymmetric(const Relation& relation)
{
    for (const auto& pair : relation)
    {
        if (relation.find(make_pair(pair.second, pair.first)) == relation.end())
        {
            return false;
        }
    }
    return true;
}

bool RelationsModule::isAntisymmetric(const Relation& relation)
{
    for (const auto& pair : relation)
    {
        if (pair.first != pair.second)
        {
            if (relation.find(make_pair(pair.second, pair.first)) != relation.end())
            {
                return false;
            }
        }
    }
    return true;
}

bool RelationsModule::isTransitive(const Relation& relation)
{
    for (const auto& pair1 : relation)
    {
        for (const auto& pair2 : relation)
        {
            if (pair1.second == pair2.first)
            {
                if (relation.find(make_pair(pair1.first, pair2.second)) == relation.end())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool RelationsModule::isEquivalenceRelation(const Relation& relation, const set<string>& domain)
{
    return isReflexive(relation, domain) && isSymmetric(relation) && isTransitive(relation);
}

bool RelationsModule::isPartialOrder(const Relation& relation, const set<string>& domain)
{
    return isReflexive(relation, domain) && isAntisymmetric(relation) && isTransitive(relation);
}

RelationsModule::Relation RelationsModule::composeRelations(const Relation& R, const Relation& S)
{
    Relation result;
    for (const auto& r : R)
    {
        for (const auto& s : S)
        {
            if (r.second == s.first)
            {
                result.insert(make_pair(r.first, s.second));
            }
        }
    }
    return result;
}

RelationsModule::Relation RelationsModule::inverseRelation(const Relation& relation)
{
    Relation result;
    for (const auto& pair : relation)
    {
        result.insert(make_pair(pair.second, pair.first));
    }
    return result;
}

RelationsModule::Relation RelationsModule::reflexiveClosure(const Relation& relation, const set<string>& domain)
{
    Relation result = relation;
    for (const string& element : domain)
    {
        result.insert(make_pair(element, element));
    }
    return result;
}

RelationsModule::Relation RelationsModule::symmetricClosure(const Relation& relation)
{
    Relation result = relation;
    Relation inverse = inverseRelation(relation);
    for (const auto& pair : inverse)
    {
        result.insert(pair);
    }
    return result;
}

RelationsModule::Relation RelationsModule::transitiveClosure(const Relation& relation, const set<string>& domain)
{
    vector<string> elements(domain.begin(), domain.end());
    int n = elements.size();

    map<string, int> indexMap;
    for (int i = 0; i < n; i++)
    {
        indexMap[elements[i]] = i;
    }

    vector<vector<bool>> matrix(n, vector<bool>(n, false));

    for (const auto& pair : relation)
    {
        int i = indexMap[pair.first];
        int j = indexMap[pair.second];
        matrix[i][j] = true;
    }

    // Warshall's algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }

    Relation result;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j])
            {
                result.insert(make_pair(elements[i], elements[j]));
            }
        }
    }

    return result;
}

vector<set<string>> RelationsModule::getEquivalenceClasses(const Relation& relation, const set<string>& domain)
{
    map<string, set<string>> classMap;

    for (const string& element : domain)
    {
        set<string> equivalenceClass;
        for (const auto& pair : relation)
        {
            if (pair.first == element)
            {
                equivalenceClass.insert(pair.second);
            }
        }
        classMap[element] = equivalenceClass;
    }

    vector<set<string>> result;
    set<string> processed;

    for (const string& element : domain)
    {
        if (processed.find(element) == processed.end())
        {
            set<string> currentClass = classMap[element];
            result.push_back(currentClass);
            for (const string& member : currentClass)
            {
                processed.insert(member);
            }
        }
    }

    return result;
}

void RelationsModule::displayRelation(const Relation& relation, const string& relationName)
{
    cout << relationName << " = { ";
    bool first = true;
    for (const auto& pair : relation)
    {
        if (!first) cout << ", ";
        cout << "(" << pair.first << "," << pair.second << ")";
        first = false;
    }
    cout << " }" << endl;
    cout << "Cardinality: |" << relationName << "| = " << relation.size() << endl;
}

void RelationsModule::displayProperties(const Relation& relation, const set<string>& domain, const string& relationName)
{
    cout << "\n========== Properties of " << relationName << " ==========\n";
    cout << "Reflexive: " << (isReflexive(relation, domain) ? "Yes" : "No") << endl;
    cout << "Symmetric: " << (isSymmetric(relation) ? "Yes" : "No") << endl;
    cout << "Antisymmetric: " << (isAntisymmetric(relation) ? "Yes" : "No") << endl;
    cout << "Transitive: " << (isTransitive(relation) ? "Yes" : "No") << endl;
    cout << "Equivalence Relation: " << (isEquivalenceRelation(relation, domain) ? "Yes" : "No") << endl;
    cout << "Partial Order: " << (isPartialOrder(relation, domain) ? "Yes" : "No") << endl;
    cout << "================================================\n";
}

void RelationsModule::displayEquivalenceClasses(const vector<set<string>>& classes)
{
    cout << "\n========== Equivalence Classes ==========\n";
    cout << "Number of classes: " << classes.size() << endl;
    for (size_t i = 0; i < classes.size(); i++)
    {
        cout << "Class " << (i + 1) << ": { ";
        bool first = true;
        for (const string& element : classes[i])
        {
            if (!first) cout << ", ";
            cout << element;
            first = false;
        }
        cout << " }" << endl;
    }
    cout << "=========================================\n";
}

set<string> RelationsModule::getDomain(const Relation& relation)
{
    set<string> domain;
    for (const auto& pair : relation)
    {
        domain.insert(pair.first);
    }
    return domain;
}

set<string> RelationsModule::getRange(const Relation& relation)
{
    set<string> range;
    for (const auto& pair : relation)
    {
        range.insert(pair.second);
    }
    return range;
}

void RelationsModule::demonstrateRelations()
{
    cout << "\n========== RELATIONS MODULE DEMONSTRATION ==========\n";

    // Example 1: Student-Course Enrollment Relation
    cout << "\n--- Example 1: Student-Course Enrollment ---\n";
    Relation enrollment;
    enrollment.insert(make_pair("S001", "CS101"));
    enrollment.insert(make_pair("S001", "Math101"));
    enrollment.insert(make_pair("S002", "CS101"));
    enrollment.insert(make_pair("S003", "Math101"));

    displayRelation(enrollment, "Enrollment");

    // Example 2: Course Prerequisite Relation (Partial Order)
    cout << "\n--- Example 2: Course Prerequisites (Partial Order) ---\n";
    set<string> courses = { "Intro", "DataStruct", "Algorithms", "AI" };

    Relation prerequisites;
    // Reflexive pairs
    prerequisites.insert(make_pair("Intro", "Intro"));
    prerequisites.insert(make_pair("DataStruct", "DataStruct"));
    prerequisites.insert(make_pair("Algorithms", "Algorithms"));
    prerequisites.insert(make_pair("AI", "AI"));

    // Prerequisite chains
    prerequisites.insert(make_pair("Intro", "DataStruct"));
    prerequisites.insert(make_pair("Intro", "Algorithms"));
    prerequisites.insert(make_pair("DataStruct", "Algorithms"));
    prerequisites.insert(make_pair("Algorithms", "AI"));
    prerequisites.insert(make_pair("Intro", "AI"));
    prerequisites.insert(make_pair("DataStruct", "AI"));

    displayRelation(prerequisites, "Prerequisites");
    displayProperties(prerequisites, courses, "Prerequisites");

    // Example 3: Equivalence Relation (Students in same year)
    cout << "\n--- Example 3: Students in Same Year (Equivalence) ---\n";
    set<string> students = { "S001", "S002", "S003", "S004" };

    Relation sameYear;
    // Year 1: S001, S002
    sameYear.insert(make_pair("S001", "S001"));
    sameYear.insert(make_pair("S001", "S002"));
    sameYear.insert(make_pair("S002", "S001"));
    sameYear.insert(make_pair("S002", "S002"));

    // Year 2: S003, S004
    sameYear.insert(make_pair("S003", "S003"));
    sameYear.insert(make_pair("S003", "S004"));
    sameYear.insert(make_pair("S004", "S003"));
    sameYear.insert(make_pair("S004", "S004"));

    displayRelation(sameYear, "SameYear");
    displayProperties(sameYear, students, "SameYear");

    vector<set<string>> classes = getEquivalenceClasses(sameYear, students);
    displayEquivalenceClasses(classes);

    // Example 4: Relation Composition
    cout << "\n--- Example 4: Relation Composition ---\n";
    Relation studentToLab;
    studentToLab.insert(make_pair("S001", "Lab1"));
    studentToLab.insert(make_pair("S002", "Lab1"));
    studentToLab.insert(make_pair("S003", "Lab2"));

    Relation labToRoom;
    labToRoom.insert(make_pair("Lab1", "Room101"));
    labToRoom.insert(make_pair("Lab2", "Room102"));

    displayRelation(studentToLab, "Student→Lab");
    displayRelation(labToRoom, "Lab→Room");

    Relation studentToRoom = composeRelations(studentToLab, labToRoom);
    displayRelation(studentToRoom, "Student→Room (Composition)");

    // Example 5: Closures
    cout << "\n--- Example 5: Closures ---\n";
    Relation simpleRel;
    simpleRel.insert(make_pair("A", "B"));
    simpleRel.insert(make_pair("B", "C"));

    set<string> simpleDomain = { "A", "B", "C" };

    displayRelation(simpleRel, "Original");

    Relation reflex = reflexiveClosure(simpleRel, simpleDomain);
    displayRelation(reflex, "Reflexive Closure");

    Relation symm = symmetricClosure(simpleRel);
    displayRelation(symm, "Symmetric Closure");

    Relation trans = transitiveClosure(simpleRel, simpleDomain);
    displayRelation(trans, "Transitive Closure");

}