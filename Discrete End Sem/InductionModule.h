#pragma once
#ifndef INDUCTIONMODULE_H
#define INDUCTIONMODULE_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include "DataBase.h"
using namespace std;
class InductionModule
{
public:
    struct ProofStep
    {
        int stepNumber;
        string stepType;        // "Base Case", "Inductive Step", "Conclusion"
        string statement;
        string justification;
        bool isValid;

        void display() const
        {
            cout << "Step " << stepNumber << ": " << stepType << "\n";
            cout << "  Statement: " << statement << "\n";
            cout << "  Justification: " << justification << "\n";
            cout << "  Status: " << (isValid ? " VALID" : " INVALID") << "\n\n";
        }
    };

    struct Proof
    {
        string courseId;
        string studentId;
        vector<ProofStep> steps;
        bool overallValid;

        void display() const 
        {
            cout << "\n" << " ================================================== " << "\n";
            cout << "MATHEMATICAL INDUCTION PROOF\n";
            cout << "Course: " << courseId << " | Student: " << studentId << "\n";
            cout << "\n" << " ================================================== " << "\n";

            for (const ProofStep& step : steps) {
                step.display();
            }

            cout << "\n" << " ================================================== " << "\n";
            cout << "OVERALL RESULT: " << (overallValid ? " VALID - Student can enroll" : " INVALID - Prerequisites not satisfied") << "\n";
            cout << "\n" << " ================================================== " << "\n";
        }
    };

private:
    DataBase* db;

public:
    InductionModule(DataBase* database) : db(database) {}

    // NORMAL INDUCTION 

    // Verify prerequisite chain using simple induction
    bool verifyPrerequisiteChain(string courseId, string studentId);

    // Generate proof using mathematical induction
    Proof generateInductionProof(string courseId, string studentId);

    // STRONG INDUCTION 

    // Verify using strong induction (checks ALL indirect prerequisites)
    bool verifyWithStrongInduction(string courseId, string studentId);

    // Generate proof using strong induction
    Proof generateStrongInductionProof(string courseId, string studentId);

    // Get prerequisite levels (for induction)
    map<string, int> getPrerequisiteLevels(string courseId);

    // Display prerequisite chain visually
    void displayPrerequisiteChain(string courseId, int indent = 0);

private:

    // Generate base case step
    ProofStep generateBaseCase(string courseId, set<string>& completed);

    // Generate inductive hypothesis step
    ProofStep generateInductiveHypothesis(int level);

    // Generate inductive step for a level
    ProofStep generateInductiveStep( string courseId, int level, set<string>& completed, map<string, int>& levels );

    // Generate conclusion
    ProofStep generateConclusion(string courseId, bool allSatisfied);

    // Recursive verification with strong induction
    bool strongInductionHelper( string courseId, set<string>& completed, set<string>& visited );
};

#endif