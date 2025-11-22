#pragma once
#ifndef RELATIONSMODULE_H
#define RELATIONSMODULE_H
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;

class RelationsModule
{
public:
    // Relation represented as set of pairs
    using Relation = set<pair<string, string>>;

    // Check if relation is reflexive
    static bool isReflexive(const Relation& relation, const set<string>& domain);

    // Check if relation is symmetric
    static bool isSymmetric(const Relation& relation);

    // Check if relation is antisymmetric
    static bool isAntisymmetric(const Relation& relation);

    // Check if relation is transitive
    static bool isTransitive(const Relation& relation);

    // Check if relation is an equivalence relation
    static bool isEquivalenceRelation(const Relation& relation, const set<string>& domain);

    // Check if relation is a partial order
    static bool isPartialOrder(const Relation& relation, const set<string>& domain);

    // Compose two relations: R ∘ S
    static Relation composeRelations(const Relation& R, const Relation& S);

    // Get inverse of a relation: R^(-1)
    static Relation inverseRelation(const Relation& relation);

    // Get reflexive closure
    static Relation reflexiveClosure(const Relation& relation, const set<string>& domain);

    // Get symmetric closure
    static Relation symmetricClosure(const Relation& relation);

    // Get transitive closure using Warshall's algorithm
    static Relation transitiveClosure(const Relation& relation, const set<string>& domain);

    // Get equivalence classes for an equivalence relation
    static vector<set<string>> getEquivalenceClasses(const Relation& relation, const set<string>& domain);

    // Display relation
    static void displayRelation(const Relation& relation, const string& relationName = "Relation");

    // Display relation properties
    static void displayProperties(const Relation& relation, const set<string>& domain, const string& relationName = "Relation");

    // Display equivalence classes
    static void displayEquivalenceClasses(const vector<set<string>>& classes);

    // Get domain of relation
    static set<string> getDomain(const Relation& relation);

    // Get range of relation
    static set<string> getRange(const Relation& relation);

    // Demonstrate relation operations
    static void demonstrateRelations();
};

#endif