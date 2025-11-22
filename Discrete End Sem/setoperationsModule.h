#pragma once
#ifndef SETOPERATIONSMODULE_H
#define SETOPERATIONSMODULE_H
#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

class SetOperations
{
public:
    // Union: A ? B
    static set<string> unionSets(const set<string>& setA, const set<string>& setB);

    // Intersection: A ? B
    static set<string> intersectionSets(const set<string>& setA, const set<string>& setB);

    // Difference: A - B
    static set<string> differenceSets(const set<string>& setA, const set<string>& setB);

    // Symmetric Difference: A ? B = (A - B) ? (B - A)
    static set<string> symmetricDifference(const set<string>& setA, const set<string>& setB);

    // Check if setA is subset of setB: A ? B
    static bool isSubset(const set<string>& setA, const set<string>& setB);

    // Check if setA is proper subset of setB: A ? B
    static bool isProperSubset(const set<string>& setA, const set<string>& setB);

    // Check if setA is superset of setB: A ? B
    static bool isSuperset(const set<string>& setA, const set<string>& setB);

    // Power Set: P(A) - returns all subsets
    static vector<set<string>> powerSet(const set<string>& inputSet);

    // Cartesian Product: A × B
    static set<pair<string, string>> cartesianProduct(const set<string>& setA, const set<string>& setB);

    // Cardinality: |A|
    static int cardinality(const set<string>& inputSet);

    // Check if two sets are equal
    static bool areEqual(const set<string>& setA, const set<string>& setB);

    // Check if sets are disjoint: A ? B = ?
    static bool areDisjoint(const set<string>& setA, const set<string>& setB);

    // Display set
    static void displaySet(const set<string>& inputSet, const string& setName = "Set");

    // Display power set
    static void displayPowerSet(const vector<set<string>>& pSet, const string& setName = "Power Set");

    // Convert vector to set
    static set<string> vectorToSet(const vector<string>& vec);

    // Convert set to vector
    static vector<string> setToVector(const set<string>& inputSet);

    // Demonstrate set operations with students and courses
    static void demonstrateSetOperations();
};

#endif