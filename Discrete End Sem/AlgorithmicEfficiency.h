#pragma once
#ifndef ALGORITHMIC_EFFICIENCY_H
#define ALGORITHMIC_EFFICIENCY_H
#include <iostream>
#include <string>
using namespace std;
class AlgorithmicEfficiency
{
public:
    // Display analysis for each module
    void analyzeConsistencyChecker();
    void analyzeDatabase();
    void analyzeInductionModule();
    void analyzeLogicEngine();
    void analyzeSetOperations();
    void analyzeRelationsModule();

    // Display summary and recommendations
    void displaySummary();
    void displayHeader();

    // Generate complete report
    void generateFullReport();
};

#endif
