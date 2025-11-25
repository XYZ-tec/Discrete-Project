#include "AlgorithmicEfficiency.h"
#include <windows.h>
#include <iomanip>

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void AlgorithmicEfficiency::displayHeader()
{
    setColor(11); // Cyan
    cout << "\n_________________________\n";
    cout << "  |                                                                      |\n";
    cout << "  |          ALGORITHMIC EFFICIENCY ANALYSIS REPORT                      |\n";
    cout << "  |                                                                      |\n";
    cout << "  ------------------------------------------------------------------------\n";
    setColor(7); // White
}

void AlgorithmicEfficiency::analyzeConsistencyChecker() {
    setColor(14); // Yellow
    cout << "\n_________________________\n";
    cout << "  MODULE: ConsistencyChecker.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: checkMissingPrerequisites() -----------------------------\n";
    setColor(10); // Green
    cout << "  Current Time Complexity: O(n * m * p)\n";
    setColor(7);
    cout << "    where n = students, m = courses per student, p = prerequisites\n";
    cout << "  Space Complexity: O(1)\n";

    setColor(12); // Red
    cout << "\n   BOTTLENECK IDENTIFIED:\n";
    setColor(7);
    cout << "     Nested loops with set.find() causing cubic complexity\n";
    cout << "     Linear search in inner loop\n";

    setColor(11); // Cyan
    cout << "\n   OPTIMIZATION SUGGESTION:\n";
    setColor(7);
    cout << "     Convert completed courses to unordered_set for O(1) lookup\n";
    cout << "     Reduces to O(n * m * p) → O(n * m) average case\n";
    cout << "     Expected Improvement: 60-80% faster for large datasets\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: checkCourseOverlaps() -------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(n²)\n";
    setColor(7);
    cout << "    where n = number of courses to check\n";
    cout << "  Space Complexity: O(n)\n";

    setColor(12);
    cout << "\n   ISSUE:\n";
    setColor(7);
    cout << "     Double nested loop for pairwise comparison\n";
    cout << "     Acceptable for small course sets (<100)\n";

    setColor(11);
    cout << "\n   OPTIMIZATION:\n";
    setColor(7);
    cout << "     Use interval tree or sweep line algorithm for O(n log n)\n";
    cout << "     Sort by start time, check adjacent intervals\n";
    cout << "     Expected Improvement: 90% faster for n>50\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: detectCircularPrerequisites() --------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V + E)\n";
    setColor(7);
    cout << "    where V = vertices (courses), E = edges (prerequisites)\n";
    cout << "  Space Complexity: O(V)\n";

    setColor(10);
    cout << "\n   WELL OPTIMIZED:\n";
    setColor(7);
    cout << "     Uses DFS with color marking (white/gray/black)\n";
    cout << "     Standard graph cycle detection algorithm\n";
    cout << "     Already at optimal complexity\n";
    cout << "     No improvement needed\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: detectUnreachableCourses() -----------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V + E)\n";
    setColor(7);
    cout << "  Space Complexity: O(V)\n";

    setColor(10);
    cout << "\n   OPTIMAL:\n";
    setColor(7);
    cout << "     Uses Kahn's algorithm (topological sort)\n";
    cout << "     Linear time complexity - cannot be improved\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: countCycles() -------------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V + E)\n";
    setColor(7);

    setColor(13); // Magenta
    cout << "\n   LOGICAL ISSUE:\n";
    setColor(7);
    cout << "     Counts back-edge encounters, not actual cycles\n";
    cout << "     May overcount in complex graphs\n";

    setColor(11);
    cout << "\n   SUGGESTION:\n";
    setColor(7);
    cout << "     Use Tarjan's algorithm for strongly connected components\n";
    cout << "     More accurate cycle counting: O(V + E)\n";
    cout << "----------------------------------------------------------------------\n";
}

void AlgorithmicEfficiency::analyzeDatabase() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  MODULE: DataBase.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: getAllPrerequisites() ------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V + E)\n";
    setColor(7);
    cout << "  where V = courses in prerequisite chain, E = prerequisite edges\n";
    cout << "  Space Complexity: O(V)\n";

    setColor(10);
    cout << "\n   EFFICIENT:\n";
    setColor(7);
    cout << "     Uses BFS for transitive closure\n";
    cout << "     Properly tracks visited nodes to avoid cycles\n";

    setColor(11);
    cout << "\n   POSSIBLE ENHANCEMENT:\n";
    setColor(7);
    cout << "     Cache results using memoization\n";
    cout << "     First call: O(V+E), subsequent: O(1)\n";
    cout << "     Trade memory for speed in query-heavy scenarios\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: getValidCourseSequence() -----------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V² + VE)\n";
    setColor(7);

    setColor(12);
    cout << "\n   INEFFICIENCY DETECTED:\n";
    setColor(7);
    cout << "     Inner loop searches entire prerequisite graph\n";
    cout << "     Unnecessary repeated iterations\n";

    setColor(11);
    cout << "\n   OPTIMIZATION:\n";
    setColor(7);
    cout << "     Build reverse adjacency list once: O(E)\n";
    cout << "     Use that for topological sort: O(V+E)\n";
    cout << "     Reduce from O(V²+VE) → O(V+E)\n";
    cout << "     Expected improvement: 70-90% for dense graphs\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: loadFromFile() / saveToFile() ------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(n)\n";
    setColor(7);
    cout << "  where n = total data entries\n";
    cout << "  Space Complexity: O(n)\n";

    setColor(10);
    cout << "\n   ACCEPTABLE:\n";
    setColor(7);
    cout << "     Linear file I/O is standard\n";
    cout << "     String parsing is straightforward\n";

    setColor(11);
    cout << "\n   MINOR IMPROVEMENT:\n";
    setColor(7);
    cout << "     Use string_view instead of substr() for parsing\n";
    cout << "     Reduce temporary string allocations\n";
    cout << "     10-20% faster parsing for large files\n";
    cout << "----------------------------------------------------------------------\n";

}

void AlgorithmicEfficiency::analyzeInductionModule() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  MODULE: InductionModule.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: getPrerequisiteLevels() ------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V + E)\n";
    setColor(7);
    cout << "  Space Complexity: O(V)\n";

    setColor(10);
    cout << "\n   OPTIMAL:\n";
    setColor(7);
    cout << "     BFS-based level assignment\n";
    cout << "     Cannot be improved asymptotically\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n--- Function: generateInductionProof() ------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(V * E)\n";
    setColor(7);
    cout << "     Checks each level with prerequisite verification\n";

    setColor(12);
    cout << "\n   POTENTIAL IMPROVEMENT:\n";
    setColor(7);
    cout << "     Redundant set lookups in nested verification\n";

    setColor(11);
    cout << "\n   OPTIMIZATION:\n";
    setColor(7);
    cout << "     Build prerequisite satisfaction cache\n";
    cout << "     Reduce repeated completed.find() calls\n";
    cout << "     30-40% improvement for deep prerequisite chains\n";
    cout << "----------------------------------------------------------------------\n";
}

void AlgorithmicEfficiency::analyzeLogicEngine() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  MODULE: Logic&InferenceModule.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: applyHypotheticalSyllogism() --------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(R²)\n";
    setColor(7);
    cout << "    where R = number of rules\n";

    setColor(12);
    cout << "\n   INEFFICIENCY:\n";
    setColor(7);
    cout << "     Double nested loop over all rules\n";
    cout << "     Checks all pairs even when no match possible\n";

    setColor(11);
    cout << "\n   OPTIMIZATION:\n";
    setColor(7);
    cout << "     Index rules by consequence in hash map\n";
    cout << "     Direct lookup instead of iteration: O(R)\n";
    cout << "     Expected improvement: 95% for R>100\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: isTautology() / isContradiction() ----------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(2^n * E)\n";
    setColor(7);
    cout << "    where n = variables, E = expression evaluation cost\n";

    setColor(13);
    cout << "\n   EXPONENTIAL - UNAVOIDABLE:\n";
    setColor(7);
    cout << "     Truth table generation is inherently exponential\n";
    cout << "     Already has safety check for n>10\n";

    setColor(11);
    cout << "\n   PRACTICAL LIMIT:\n";
    setColor(7);
    cout << "     Current limit of 10 variables is reasonable\n";
    cout << "     2^10 = 1024 evaluations (manageable)\n";
    cout << "     Could use SAT solver for larger expressions\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: forwardChaining() --------------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(I * R * F)\n";
    setColor(7);
    cout << "    where I = iterations, R = rules, F = facts\n";

    setColor(12);
    cout << "\n   CONCERN:\n";
    setColor(7);
    cout << "     No early termination if fixpoint reached\n";
    cout << "     Hard-coded iteration limit\n";

    setColor(11);
    cout << "\n   IMPROVEMENT:\n";
    setColor(7);
    cout << "     Use Rete algorithm for production systems\n";
    cout << "     Add smarter convergence detection\n";
    cout << "----------------------------------------------------------------------\n";
}

void AlgorithmicEfficiency::analyzeSetOperations() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  MODULE: SetOperationsModule.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: powerSet() --------------------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(2^n * n)\n";
    setColor(7);
    cout << "  where n = set size\n";
    cout << "  Space Complexity: O(2^n * n)\n";

    setColor(13);
    cout << "\n   EXPONENTIAL - EXPECTED:\n";
    setColor(7);
    cout << "     Power set has 2^n elements by definition\n";
    cout << "     Cannot be improved asymptotically\n";

    setColor(11);
    cout << "\n   PRACTICAL CONSIDERATION:\n";
    setColor(7);
    cout << "     Add safety check for n>20 (2^20 = 1M subsets)\n";
    cout << "     Current implementation is standard\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: union/intersection/difference -------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(n + m)\n";
    setColor(7);
    cout << "  where n, m = sizes of input sets\n";

    setColor(10);
    cout << "\n   OPTIMAL:\n";
    setColor(7);
    cout << "     Using std::set with balanced tree (O(log n) operations)\n";
    cout << "     Already efficient for these operations\n";
    cout << "     Could use unordered_set for O(1) average case\n";
    cout << "----------------------------------------------------------------------\n";
}

void AlgorithmicEfficiency::analyzeRelationsModule() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  MODULE: RelationsModule.cpp\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- Function: transitiveClosure() -----------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(n³)\n";
    setColor(7);
    cout << "  using Warshall's algorithm\n";
    cout << "  Space Complexity: O(n²)\n";

    setColor(10);
    cout << "\n   STANDARD ALGORITHM:\n";
    setColor(7);
    cout << "     Warshall's is the standard approach\n";
    cout << "     Optimal for dense graphs\n";

    setColor(11);
    cout << "\n   ALTERNATIVE FOR SPARSE:\n";
    setColor(7);
    cout << "     Use DFS/BFS from each vertex: O(V * (V+E))\n";
    cout << "     Better when |E| << n²\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- Function: isTransitive() ---------------------------------------------------\n";
    setColor(10);
    cout << "  Current Time Complexity: O(R²)\n";
    setColor(7);
    cout << "  where R = relation size (number of pairs)\n";

    setColor(12);
    cout << "\n   INEFFICIENCY:\n";
    setColor(7);
    cout << "     Nested loop checks all pair combinations\n";

    setColor(11);
    cout << "\n   OPTIMIZATION:\n";
    setColor(7);
    cout << "     Index pairs by first element in multimap\n";
    cout << "     Reduce unnecessary comparisons\n";
    cout << "     Can achieve O(R * D) where D = avg degree\n";
    cout << "----------------------------------------------------------------------\n";
}

void AlgorithmicEfficiency::displaySummary() {
    setColor(14);
    cout << "\n_________________________\n";
    cout << "  OVERALL SUMMARY & RECOMMENDATIONS\n";
    cout << "\n_________________________\n";
    setColor(7);

    cout << "\n---- HIGH PRIORITY OPTIMIZATIONS ------------------------------------------------\n";
    setColor(12);
    cout << "  1. getValidCourseSequence(): O(V²+VE) → O(V+E)\n";
    cout << "  2. applyHypotheticalSyllogism(): O(R²) → O(R)\n";
    cout << "  3. checkCourseOverlaps(): O(n²) → O(n log n)\n";
    setColor(7);
    cout << "\n  Impact: 60-90% performance improvement on large datasets\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- MEDIUM PRIORITY ------------------------------------------------------------\n";
    setColor(13);
    cout << "  1. Add memoization to getAllPrerequisites()\n";
    cout << "  2. Use unordered_set instead of set where order doesn't matter\n";
    cout << "  3. Optimize isTransitive() with indexing\n";
    setColor(7);
    cout << "\n  Impact: 30-50% improvement for repeated queries\n";
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- ALREADY OPTIMAL -----------------------------------------------------------\n";
    setColor(10);
    cout << "   detectCircularPrerequisites() - O(V+E)\n";
    cout << "   detectUnreachableCourses() - O(V+E)\n";
    cout << "   getPrerequisiteLevels() - O(V+E)\n";
    cout << "   Set operations (union, intersection) - O(n+m)\n";
    setColor(7);
    cout << "----------------------------------------------------------------------\n";

    cout << "\n---- SPACE-TIME TRADEOFFS ------------------------------------------------------\n";
    setColor(11);
    cout << "  Consider these for query-heavy scenarios:\n";
    setColor(7);
    cout << "   Cache transitive prerequisite closures\n";
    cout << "   Pre-compute topological orderings\n";
    cout << "   Index rules/facts by key attributes\n";
    cout << "\n Trade: +30-50% memory for -70-90% query time\n";
    cout << "----------------------------------------------------------------------\n";

    setColor(10);
    cout << "\n_________________________\n";
    cout << "  |  Overall Assessment: Good implementation with room for optimization |\n";
    cout << "  |  Estimated Performance Gain: 50-80% with suggested improvements     |  \n";
    cout << "  -----------------------------------------------------------------------\n";

    setColor(7);
}

void AlgorithmicEfficiency::generateFullReport() {
    displayHeader();
    analyzeConsistencyChecker();
    analyzeDatabase();
    analyzeInductionModule();
    analyzeLogicEngine();
    analyzeSetOperations();
    analyzeRelationsModule();
    displaySummary();

    setColor(7); // Reset to white
    cout << "\n";
}