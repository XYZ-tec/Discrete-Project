#pragma once
#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DataBase.h"
using namespace std;

class LogicEngine {
public:
    // Structure for logical rule
    struct Rule {
        string ruleId;
        string condition;      // IF part (antecedent)
        string consequence;    // THEN part (consequent)
        string ruleType;       // "IMPLIES", "AND", "OR", "NOT"
        bool isActive;

        void display() const {
            cout << "Rule " << ruleId << ": ";
            cout << "IF (" << condition << ") THEN (" << consequence << ")";
            cout << " [" << (isActive ? "ACTIVE" : "INACTIVE") << "]\n";
        }
    };

    // Structure for fact
    struct Fact {
        string factId;
        string statement;
        bool truthValue;

        void display() const {
            cout << "Fact " << factId << ": " << statement
                << " = " << (truthValue ? "TRUE" : "FALSE") << "\n";
        }
    };

    // Structure for conflict report
    struct Conflict {
        string conflictType;
        string description;
        vector<string> involvedEntities;
        string severity;  // "HIGH", "MEDIUM", "LOW"

        void display() const {
            cout << "[" << severity << "] " << conflictType << "\n";
            cout << "  Description: " << description << "\n";
            cout << "  Entities: ";
            for (const string& entity : involvedEntities) {
                cout << entity << " ";
            }
            cout << "\n";
        }
    };

private:
    DataBase* db;
    map<string, Rule> rules;           // ruleId -> Rule
    map<string, Fact> facts;           // factId -> Fact
    vector<Conflict> conflicts;
    int nextRuleId;
    int nextFactId;

public:
    LogicEngine(DataBase* database) : db(database), nextRuleId(1), nextFactId(1) {}

    // === FILE HANDLING ===

    // Load rules from file
    bool loadRulesFromFile(string filename);

    // Save rules to file
    bool saveRulesToFile(string filename) const;

    // Load facts from file
    bool loadFactsFromFile(string filename);

    // Save facts to file
    bool saveFactsToFile(string filename) const;

    // Save conflicts to file
    bool saveConflictsToFile(string filename) const;

    // === RULE MANAGEMENT ===

    // Add a logical rule
    string addRule(string condition, string consequence, string ruleType = "IMPLIES");

    // Parse natural language rule to logical form
    Rule parseNaturalLanguageRule(string naturalLanguage);

    // Remove a rule
    void removeRule(string ruleId);

    // Activate/Deactivate rule
    void setRuleActive(string ruleId, bool active);

    // Display all rules
    void displayAllRules() const;

    // Get rule count
    int getRuleCount() const { return rules.size(); }

    // === FACT MANAGEMENT ===

    // Add a fact
    string addFact(string statement, bool truthValue);

    // Update fact truth value
    void updateFact(string factId, bool truthValue);

    // Check if fact exists
    bool factExists(string statement) const;

    // Get fact truth value
    bool getFact(string statement) const;

    // Display all facts
    void displayAllFacts() const;

    // Get fact count
    int getFactCount() const { return facts.size(); }

    // === INFERENCE ENGINE ===

    // Perform forward chaining (derive new facts from existing ones)
    vector<Fact> forwardChaining();

    // Apply Modus Ponens: If (P → Q) and P is true, then Q is true
    vector<Fact> applyModusPonens();

    // Apply Modus Tollens: If (P → Q) and Q is false, then P is false
    vector<Fact> applyModusTollens();

    // Apply Hypothetical Syllogism: If (P → Q) and (Q → R), then (P → R)
    vector<Rule> applyHypotheticalSyllogism();

    // Apply all inference rules and return summary
    void performInference();

    // === CONFLICT DETECTION ===

    // Detect all conflicts in the system
    vector<Conflict> detectAllConflicts();

    // Check for contradictory rules
    bool hasContradictoryRules();

    // Check for logical inconsistencies
    vector<string> findInconsistencies();

    // Display all conflicts
    void displayConflicts() const;

    // Clear all conflicts
    void clearConflicts() { conflicts.clear(); }

    // === POLICY ENFORCEMENT ===

    // Verify academic policies
    bool verifyPolicy(string policyRule);

    // Check if a specific rule is satisfied
    bool isRuleSatisfied(string ruleId);

    // Get violated policies
    vector<string> getViolatedPolicies();

    // === UTILITY ===

    // Evaluate a logical expression
    bool evaluateExpression(string expression);

    // Check if expression is a tautology
    bool isTautology(string expression);

    // Check if expression is a contradiction
    bool isContradiction(string expression);

    // Generate truth table for expression
    void displayTruthTable(string expression, vector<string> variables);

    // Display statistics
    void displayStatistics() const;

private:
    // === HELPER METHODS ===

    // Parse condition/consequence into components
    vector<string> parseComponents(string statement);

    // Extract variables from expression
    vector<string> extractVariables(string expression);

    // Evaluate logical operators
    bool evaluateAND(bool a, bool b) { return a && b; }
    bool evaluateOR(bool a, bool b) { return a || b; }
    bool evaluateNOT(bool a) { return !a; }
    bool evaluateIMPLIES(bool a, bool b) { return !a || b; }

    // Check if two statements are equivalent
    bool areEquivalent(string stmt1, string stmt2);

    // Trim whitespace
    string trim(const string& str);
};

#endif