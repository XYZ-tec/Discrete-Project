#include "InductionModule.h"

bool InductionModule::verifyPrerequisiteChain( string courseId, string studentId ) 
{
    Student* student = db->getStudent(studentId);
    if (!student) 
    {
        cout << "Error: Student not found\n";
        return false;
    }

    Courses* course = db->getCourse(courseId);
    if (!course)
    {
        cout << "Error: Course not found\n";
        return false;
    }

    set<string> allPrereqs = db->getAllPrerequisites(courseId);

    for (const string& prereq : allPrereqs)
    {
        if (!student->hasCompletedCourse(prereq)) 
        {
            return false;
        }
    }

    return true;
}

InductionModule::Proof InductionModule::generateInductionProof( string courseId, string studentId ) 
{
    Proof proof;
    proof.courseId = courseId;
    proof.studentId = studentId;
    proof.overallValid = true;

    Student* student = db->getStudent(studentId);
    if (!student) 
    {
        proof.overallValid = false;
        return proof;
    }

    // Get completed courses as set
    set<string> completed;
    const vector<string>& completedVec = student->getCompletedCourses();
    for (const string& c : completedVec)
    {
        completed.insert(c);
    }

    map<string, int> levels = getPrerequisiteLevels(courseId);

    int stepNum = 1;

    // STEP 1: Base Case
    ProofStep baseCase = generateBaseCase(courseId, completed);
    baseCase.stepNumber = stepNum++;
    proof.steps.push_back(baseCase);

    if (!baseCase.isValid)
    {
        proof.overallValid = false;
        ProofStep conclusion = generateConclusion(courseId, false);
        conclusion.stepNumber = stepNum++;
        proof.steps.push_back(conclusion);
        return proof;
    }

    // STEP 2: Inductive Hypothesis
    int maxLevel = 0;
    for (auto& pair : levels)
    {
        maxLevel = max(maxLevel, pair.second);
    }

    if (maxLevel > 0)
    {
        ProofStep hypothesis = generateInductiveHypothesis(maxLevel);
        hypothesis.stepNumber = stepNum++;
        proof.steps.push_back(hypothesis);

        // STEP 3+: Inductive Steps for each level
        for (int level = 1; level <= maxLevel; level++)
        {
            ProofStep inductiveStep = generateInductiveStep(courseId, level, completed, levels);
            inductiveStep.stepNumber = stepNum++;
            proof.steps.push_back(inductiveStep);

            if (!inductiveStep.isValid)
            {
                proof.overallValid = false;
                break;
            }
        }
    }

    // FINAL STEP: Conclusion
    ProofStep conclusion = generateConclusion(courseId, proof.overallValid);
    conclusion.stepNumber = stepNum++;
    proof.steps.push_back(conclusion);

    return proof;
}

bool InductionModule::verifyWithStrongInduction( string courseId, string studentId ) 
{
    Student* student = db->getStudent(studentId);
    if (!student) 
        return false;

    set<string> completed;
    const vector<string>& completedVec = student->getCompletedCourses();
    for (const string& c : completedVec)
    {
        completed.insert(c);
    }

    set<string> visited;
    return strongInductionHelper(courseId, completed, visited);
}

InductionModule::Proof InductionModule::generateStrongInductionProof( string courseId, string studentId )
{
    Proof proof;
    proof.courseId = courseId;
    proof.studentId = studentId;

    Student* student = db->getStudent(studentId);
    if (!student) 
    {
        proof.overallValid = false;
        return proof;
    }

    set<string> completed;
    const vector<string>& completedVec = student->getCompletedCourses();
    for (const string& c : completedVec) 
    {
        completed.insert(c);
    }

    int stepNum = 1;

    // STEP 1: Strong Induction Base Case
    ProofStep base;
    base.stepNumber = stepNum++;
    base.stepType = "Base Case (Strong Induction)";
    base.statement = "P(0): Verify all foundational courses (with no prerequisites)";

    set<string> allPrereqs = db->getAllPrerequisites(courseId);
    vector<string> baseCourses;

    for (const string& prereq : allPrereqs)
    {
        Courses* c = db->getCourse(prereq);
        if (c && c->getPrerequisites().empty())
        {
            baseCourses.push_back(prereq);
        }
    }

    base.justification = "Base courses required: ";
    base.isValid = true;

    for (const string& bc : baseCourses) 
    {
        base.justification += bc + " ";
        if (completed.find(bc) == completed.end()) 
        {
            base.justification += "(MISSING) ";
            base.isValid = false;
        }
        else
        {
            base.justification += "(All Good) ";
        }
    }

    if (baseCourses.empty())
    {
        base.justification = "No base courses required (course has no prerequisites)";
        base.isValid = true;
    }

    proof.steps.push_back(base);

    if (!base.isValid) 
    {
        proof.overallValid = false;
        ProofStep conclusion = generateConclusion(courseId, false);
        conclusion.stepNumber = stepNum++;
        proof.steps.push_back(conclusion);
        return proof;
    }

    // STEP 2: Strong Inductive Hypothesis
    ProofStep hypothesis;
    hypothesis.stepNumber = stepNum++;
    hypothesis.stepType = "Strong Inductive Hypothesis";
    hypothesis.statement = "Assume P(k) is true for ALL k < n";
    hypothesis.justification = "Assume that for every prerequisite level k (from 0 to n-1), all courses at that level have their prerequisites satisfied.";
    hypothesis.isValid = true;
    proof.steps.push_back(hypothesis);

    // STEP 3: Strong Inductive Step
    ProofStep inductiveStep;
    inductiveStep.stepNumber = stepNum++;
    inductiveStep.stepType = "Strong Inductive Step";
    inductiveStep.statement = "Prove P(n): For course " + courseId + ", verify ALL prerequisites";

    inductiveStep.justification = "Checking all prerequisites recursively:\n";
    inductiveStep.isValid = true;

    Courses* targetCourse = db->getCourse(courseId);
    if (targetCourse)
    {
        const vector<string>& directPrereqs = targetCourse->getPrerequisites();

        for (const string& prereq : directPrereqs)
        {
            inductiveStep.justification += "  - " + prereq + ": ";
            if (completed.find(prereq) == completed.end())
            {
                inductiveStep.justification += "NOT COMPLETED \n";
                inductiveStep.isValid = false;
            }
            else
            {
                // Check indirect prerequisites recursively 
                set<string> indirectPrereqs = db->getAllPrerequisites(prereq);
                bool allIndirectSatisfied = true;

                for (const string& indirect : indirectPrereqs) 
                {
                    if (completed.find(indirect) == completed.end())
                    {
                        allIndirectSatisfied = false;
                        break;
                    }
                }


                if (allIndirectSatisfied)
                {
                    inductiveStep.justification += "COMPLETED (and all its prerequisites) \n";
                }
                else
                {
                    inductiveStep.justification += "COMPLETED but missing indirect prerequisites \n";
                    inductiveStep.isValid = false;
                }
            }
        }
    }

    proof.steps.push_back(inductiveStep);
    proof.overallValid = inductiveStep.isValid;

    // STEP 4: Conclusion
    ProofStep conclusion = generateConclusion(courseId, proof.overallValid);
    conclusion.stepNumber = stepNum++;
    proof.steps.push_back(conclusion);

    return proof;
}

map<string, int> InductionModule::getPrerequisiteLevels(string courseId)
{
    map<string, int> levels;
    queue<string> q;
    set<string> visited;

    q.push(courseId);
    visited.insert(courseId);
    levels[courseId] = 0;

    // BFS to find levels
    while (!q.empty())
    {
        string current = q.front();
        q.pop();
        Courses* course = db->getCourse(current);
        if (!course) continue;

        const vector<string>& prereqs = course->getPrerequisites();
        for (const string& prereq : prereqs) 
        {
            if (visited.find(prereq) == visited.end()) 
            {
                visited.insert(prereq);
                q.push(prereq);
                levels[prereq] = levels[current] + 1;
            }
        }
    }

    // Reverse levels (base courses should be level 0)
    int maxLevel = 0;
    for (auto& pair : levels)
    {
        maxLevel = max(maxLevel, pair.second);
    }

    for (auto& pair : levels)
    {
        pair.second = maxLevel - pair.second;
    }

    return levels;
}

void InductionModule::displayPrerequisiteChain(string courseId, int indent)
{
    Courses* course = db->getCourse(courseId);
    if (!course)
        return;

    cout << string(indent * 2, ' ') << "|__" << courseId << " (" << course->getName() << ")\n";

    const vector<string>& prereqs = course->getPrerequisites();
    for (const string& prereq : prereqs)
    {
        displayPrerequisiteChain(prereq, indent + 1);
    }
}

InductionModule::ProofStep InductionModule::generateBaseCase( string courseId, set<string>& completed ) 
{
    ProofStep step;
    step.stepType = "Base Case";
    step.statement = "P(0): Verify foundational courses (level 0)";
    step.isValid = true;

    set<string> allPrereqs = db->getAllPrerequisites(courseId);
    vector<string> baseCourses;

    for (const string& prereq : allPrereqs)
    {
        Courses* c = db->getCourse(prereq);
        if (c && c->getPrerequisites().empty()) 
        {
            baseCourses.push_back(prereq);
        }
    }

    if (baseCourses.empty())
    {
        step.justification = "No foundational courses required. Base case trivially satisfied.";
        return step;
    }

    step.justification = "Foundational courses: ";
    for (const string& bc : baseCourses) 
    {
        step.justification += bc + " ";
        if (completed.find(bc) == completed.end()) 
        {
            step.justification += "(NOT COMPLETED) ";
            step.isValid = false;
        }
        else 
        {
            step.justification += "(ALL GOOD) ";
        }
    }

    return step;
}

InductionModule::ProofStep InductionModule::generateInductiveHypothesis(int maxLevel)
{
    ProofStep step;
    step.stepType = "Inductive Hypothesis";
    step.statement = "Assume P(k) is true for k = 0, 1, 2, ..., " + to_string(maxLevel - 1);
    step.justification = "Assume all courses at levels 0 through " + to_string(maxLevel - 1) +
        " have their prerequisites properly satisfied.";
    step.isValid = true;
    return step;
}

InductionModule::ProofStep InductionModule::generateInductiveStep( string courseId, int level, set<string>& completed, map<string, int>& levels )
{
    ProofStep step;
    step.stepType = "Inductive Step";
    step.statement = "P(" + to_string(level) + "): Verify courses at level " + to_string(level);
    step.isValid = true;

    // Find courses at this level
    vector<string> coursesAtLevel;
    for (auto& pair : levels) 
    {
        if (pair.second == level)
        {
            coursesAtLevel.push_back(pair.first);
        }
    }

    step.justification = "Courses at level " + to_string(level) + ": ";

    for (const string& c : coursesAtLevel)
    {
        step.justification += c + " ";

        Courses* course = db->getCourse(c);
        if (course)
        {
            const vector<string>& prereqs = course->getPrerequisites();
            bool allPrereqsSatisfied = true;

            for (const string& prereq : prereqs) 
            {
                if (completed.find(prereq) == completed.end()) 
                {
                    allPrereqsSatisfied = false;
                    step.justification += "(Missing: " + prereq + ") ";
                    break;
                }
            }

            if (!allPrereqsSatisfied)
            {
                step.isValid = false;
            }
            else
            {
                step.justification += "(✓) ";
            }
        }
    }

    return step;
}

InductionModule::ProofStep InductionModule::generateConclusion( string courseId, bool allSatisfied ) 
{
    ProofStep step;
    step.stepType = "Conclusion";
    step.statement = "By mathematical induction, the claim is " + string(allSatisfied ? "proven" : "disproven");

    if (allSatisfied)
    {
        step.justification = "All prerequisites for " + courseId + " are satisfied. "
            "Student can enroll in this course.";
        step.isValid = true;
    }
    else 
    {
        step.justification = "Not all prerequisites for " + courseId + " are satisfied. "
            "Student CANNOT enroll in this course.";
        step.isValid = false;
    }

    return step;
}

bool InductionModule::strongInductionHelper( string courseId, set<string>& completed, set<string>& visited ) 
{
    if (visited.find(courseId) != visited.end())
    {
        return true;
    }
    visited.insert(courseId);

    Courses* course = db->getCourse(courseId);
    if (!course) 
        return false;

    const vector<string>& prereqs = course->getPrerequisites();

    // Base case: no prerequisites
    if (prereqs.empty()) 
    {
        return true;
    }

    // Strong induction: check ALL prerequisites recursively
    for (const string& prereq : prereqs) 
    {
        // Must be completed
        if (completed.find(prereq) == completed.end()) 
        {
            return false;
        }

        // Recursively verify prerequisite's chain
        if (!strongInductionHelper(prereq, completed, visited)) 
        {
            return false;
        }
    }

    return true;
}