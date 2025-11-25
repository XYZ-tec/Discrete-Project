#include "Logic&InferenceModule.h"
#include <algorithm>

bool LogicEngine::loadRules(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << " No existing rules file. Starting fresh.\n";
        return false;
    }

    string line;
    int loadedCount = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        // Simple format: RuleID|Condition|Consequence|Type|Active
        // Example: R1|Prof_Smith_teaches_CS101|Lab_must_be_LabA|IMPLIES|1

        stringstream ss(line);
        string ruleId, condition, consequence, ruleType, activeStr;

        getline(ss, ruleId, '|');
        getline(ss, condition, '|');
        getline(ss, consequence, '|');
        getline(ss, ruleType, '|');
        getline(ss, activeStr);

        Rule rule;
        rule.ruleId = ruleId;
        rule.condition = condition;
        rule.consequence = consequence;
        rule.ruleType = ruleType;
        rule.isActive = (activeStr == "1");

        rules[rule.ruleId] = rule;
        loadedCount++;

        // Update nextRuleId
        if (rule.ruleId[0] == 'R')
        {
            int id = stoi(rule.ruleId.substr(1));
            if (id >= nextRuleId)
                nextRuleId = id + 1;
        }
    }

    file.close();
    cout << " Loaded " << loadedCount << " rules from " << filename << endl;
    return true;
}

bool LogicEngine::saveRules(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << " Error: Cannot create file " << filename << endl;
        return false;
    }

    for (const auto& pair : rules)
    {
        const Rule& rule = pair.second;
        file << rule.ruleId << "|"
            << rule.condition << "|"
            << rule.consequence << "|"
            << rule.ruleType << "|"
            << (rule.isActive ? "1" : "0") << "\n";
    }

    file.close();
    cout << " Saved " << rules.size() << " rules to " << filename << endl;
    return true;
}

bool LogicEngine::loadFacts(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << " No existing facts file. Starting fresh.\n";
        return false;
    }

    string line;
    int loadedCount = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        // Simple format: FactID|Statement|TruthValue
        // Example: F1|Prof_Smith_teaches_CS101|1

        stringstream ss(line);
        string factId, statement, valueStr;

        getline(ss, factId, '|');
        getline(ss, statement, '|');
        getline(ss, valueStr);

        Fact fact;
        fact.factId = factId;
        fact.statement = statement;
        fact.truthValue = (valueStr == "1");

        facts[fact.factId] = fact;
        loadedCount++;

        // Update nextFactId
        if (fact.factId[0] == 'F')
        {
            int id = stoi(fact.factId.substr(1));
            if (id >= nextFactId)
                nextFactId = id + 1;
        }
    }

    file.close();
    cout << " Loaded " << loadedCount << " facts from " << filename << endl;
    return true;
}

bool LogicEngine::saveFacts(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << " Error: Cannot create file " << filename << endl;
        return false;
    }

    for (const auto& pair : facts)
    {
        const Fact& fact = pair.second;
        file << fact.factId << "|"
            << fact.statement << "|"
            << (fact.truthValue ? "1" : "0") << "\n";
    }

    file.close();
    cout << " Saved " << facts.size() << " facts to " << filename << endl;
    return true;
}

string LogicEngine::addRule(string condition, string consequence, string ruleType) 
{
    Rule rule;
    rule.ruleId = "R" + to_string(nextRuleId++);
    rule.condition = condition;
    rule.consequence = consequence;
    rule.ruleType = ruleType;
    rule.isActive = true;
    rules[rule.ruleId] = rule;
    return
        rule.ruleId;
}

LogicEngine::Rule LogicEngine::parseNaturalLanguageRule(string naturalLanguage) 
{
    Rule rule;
    rule.ruleId = "R" + to_string(nextRuleId++);
    rule.ruleType = "IMPLIES";
    rule.isActive = true;

    // Find "IF" and "THEN" keywords (case-insensitive)
    string lower = naturalLanguage;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    auto ifPos = lower.find("if");
    auto thenPos = lower.find("then");

    if (ifPos != string::npos && thenPos != string::npos)
    {
        rule.condition = naturalLanguage.substr(ifPos + 2, thenPos - ifPos - 2);
        rule.consequence = naturalLanguage.substr(thenPos + 4);
        rule.condition = trim(rule.condition);
        rule.consequence = trim(rule.consequence);
    }
    else 
    {
        rule.condition = naturalLanguage;
        rule.consequence = "unknown";
    }

    return rule;
}

void LogicEngine::removeRule(string ruleId) 
{
    rules.erase(ruleId);
}

void LogicEngine::setRuleActive(string ruleId, bool active) 
{
    if (rules.find(ruleId) != rules.end()) 
    {
        rules[ruleId].isActive = active;
    }
}

void LogicEngine::displayAllRules() const
{
    cout << "\n========== LOGICAL RULES ==========\n";
    cout << "Total Rules: " << rules.size() << "\n\n";

    for (const auto& pair : rules)
    {
        pair.second.display();
    }

    cout << "===================================\n";
}

string LogicEngine::addFact(string statement, bool truthValue)
{
    // Check if fact already exists
    for (const auto& pair : facts)
    {
        if (pair.second.statement == statement)
        {
            // Update existing fact
            facts[pair.first].truthValue = truthValue;
            return
                pair.first;
        }
    }

    // Add new fact
    Fact fact;
    fact.factId = "F" + to_string(nextFactId++);
    fact.statement = statement;
    fact.truthValue = truthValue;
    facts[fact.factId] = fact;
    return 
        fact.factId;
}

void LogicEngine::updateFact(string factId, bool truthValue)
{
    if (facts.find(factId) != facts.end()) 
    {
        facts[factId].truthValue = truthValue;
    }
}

bool LogicEngine::factExists(string statement) const
{
    for (const auto& pair : facts) 
    {
        if (pair.second.statement == statement) 
        {
            return true;
        }
    }
    return false;
}

bool LogicEngine::getFact(string statement) const
{
    for (const auto& pair : facts)
    {
        if (pair.second.statement == statement)
        {
            return pair.second.truthValue;
        }
    }
    return false;
}

void LogicEngine::displayAllFacts() const 
{
    cout << "\n========== KNOWN FACTS ==========\n";
    cout << "Total Facts: " << facts.size() << "\n\n";

    for (const auto& pair : facts) 
    {
        pair.second.display();
    }

    cout << "=================================\n";
}

vector<LogicEngine::Fact> LogicEngine::forwardChaining()
{
    vector<Fact> newFacts;
    bool changed = true;
    int iterations = 0;
    const int MAX_ITERATIONS = 100; // Prevent infinite loops

    while (changed && iterations < MAX_ITERATIONS)
    {
        changed = false;
        iterations++;
        vector<Fact> derived = applyModusPonens();
        for (const Fact& newFact : derived)
        {
            if (!factExists(newFact.statement))
            {
                facts[newFact.factId] = newFact;
                newFacts.push_back(newFact);
                changed = true;
            }
        }
    }

    return newFacts;
}

vector<LogicEngine::Fact> LogicEngine::applyModusPonens()
{
    vector<Fact> derivedFacts;

    // Modus Ponens: If (P → Q) and P is true, then Q is true
    for (const auto& rulePair : rules) 
    {
        const Rule& rule = rulePair.second;

        if (!rule.isActive || rule.ruleType != "IMPLIES") 
            continue;

        // Check if condition (P) is true
        if (factExists(rule.condition) && getFact(rule.condition)) 
        {
            // Check if consequence (Q) is not already known
            if (!factExists(rule.consequence)) 
            {
                Fact newFact;
                newFact.factId = "F" + to_string(nextFactId++);
                newFact.statement = rule.consequence;
                newFact.truthValue = true;
                derivedFacts.push_back(newFact);
            }
        }
    }
    return derivedFacts;
}

vector<LogicEngine::Fact> LogicEngine::applyModusTollens()
{
    vector<Fact> derivedFacts;

    // Modus Tollens: If (P → Q) and Q is false, then P is false
    for (const auto& rulePair : rules)
    {
        const Rule& rule = rulePair.second;

        if (!rule.isActive || rule.ruleType != "IMPLIES")
            continue;

        // Check if consequence (Q) is false
        if (factExists(rule.consequence) && !getFact(rule.consequence)) 
        {
            // Check if condition (P) is not already known to be false
            if (!factExists(rule.condition))
            {
                Fact newFact;
                newFact.factId = "F" + to_string(nextFactId++);
                newFact.statement = rule.condition;
                newFact.truthValue = false;

                derivedFacts.push_back(newFact);
            }
        }
    }

    return derivedFacts;
}

vector<LogicEngine::Rule> LogicEngine::applyHypotheticalSyllogism() 
{
    vector<Rule> derivedRules;

    // Hypothetical Syllogism: If (P → Q) and (Q → R), then (P → R)
    for (const auto& rule1Pair : rules) 
    {
        const Rule& rule1 = rule1Pair.second;
        if (!rule1.isActive || rule1.ruleType != "IMPLIES")
            continue;
        for (const auto& rule2Pair : rules) 
        {
            const Rule& rule2 = rule2Pair.second;
            if (!rule2.isActive || rule2.ruleType != "IMPLIES") 
                continue;

            // Check if rule1's consequence matches rule2's condition
            if (rule1.consequence == rule2.condition) 
            {
                // Create new rule: rule1.condition → rule2.consequence
                Rule newRule;
                newRule.ruleId = "R" + to_string(nextRuleId++);
                newRule.condition = rule1.condition;
                newRule.consequence = rule2.consequence;
                newRule.ruleType = "IMPLIES";
                newRule.isActive = true;

                // Check if this rule doesn't already exist
                bool exists = false;
                for (const auto& existingPair : rules)
                {
                    if (existingPair.second.condition == newRule.condition && existingPair.second.consequence == newRule.consequence) 
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                {
                    derivedRules.push_back(newRule);
                    rules[newRule.ruleId] = newRule; // Add to rules
                }
            }
        }
    }

    return derivedRules;
}

void LogicEngine::performInference()
{
    cout << "\n========== PERFORMING INFERENCE ==========\n";

    // Apply Modus Ponens
    vector<Fact> modusPonensResults = applyModusPonens();
    cout << "Modus Ponens: Derived " << modusPonensResults.size() << " new facts\n";

    // Apply Modus Tollens
    vector<Fact> modusTollensResults = applyModusTollens();
    cout << "Modus Tollens: Derived " << modusTollensResults.size() << " new facts\n";

    // Apply Hypothetical Syllogism
    vector<Rule> syllogismResults = applyHypotheticalSyllogism();
    cout << "Hypothetical Syllogism: Derived " << syllogismResults.size() << " new rules\n";

    // Forward Chaining
    vector<Fact> chainedFacts = forwardChaining();
    cout << "Forward Chaining: Derived " << chainedFacts.size() << " new facts\n";

    cout << "==========================================\n";
}


vector<LogicEngine::Conflict> LogicEngine::detectAllConflicts()
{
    conflicts.clear();

    // Check contradictory facts
    for (const auto& fact1 : facts)
    {
        for (const auto& fact2 : facts) 
        {
            if (fact1.first != fact2.first)
            {
                // Simple contradiction check
                if (fact1.second.statement == "NOT_" + fact2.second.statement || fact2.second.statement == "NOT_" + fact1.second.statement)
                {
                    if (fact1.second.truthValue == fact2.second.truthValue)
                    {
                        Conflict conflict;
                        conflict.conflictType = "LOGICAL_CONTRADICTION";
                        conflict.description = "Facts " + fact1.first + " and " + fact2.first + " are contradictory";
                        conflict.involvedEntities.push_back(fact1.first);
                        conflict.involvedEntities.push_back(fact2.first);
                        conflict.severity = "HIGH";
                        conflicts.push_back(conflict);
                    }
                }
            }
        }
    }

    // Check for rule violations
    for (const auto& rulePair : rules)
    {
        const Rule& rule = rulePair.second;

        if (!rule.isActive)
            continue;

        if (factExists(rule.condition) && getFact(rule.condition))
        {
            if (factExists(rule.consequence) && !getFact(rule.consequence))
            {
                Conflict conflict;
                conflict.conflictType = "RULE_VIOLATION";
                conflict.description = "Rule " + rule.ruleId + " violated: " + rule.condition + " → " + rule.consequence;
                conflict.involvedEntities.push_back(rule.ruleId);
                conflict.severity = "MEDIUM";
                conflicts.push_back(conflict);
            }
        }
    }

    return conflicts;
}

bool LogicEngine::hasContradictoryRules()
{
    for (const auto& rule1Pair : rules)
    {
        const Rule& rule1 = rule1Pair.second;

        for (const auto& rule2Pair : rules)
        {
            const Rule& rule2 = rule2Pair.second;

            if (rule1.ruleId != rule2.ruleId) 
            {
                // Check if same condition leads to opposite consequences
                if (rule1.condition == rule2.condition) 
                {
                    if (rule1.consequence == "NOT_" + rule2.consequence || rule2.consequence == "NOT_" + rule1.consequence) 
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

vector<string> LogicEngine::findInconsistencies() 
{
    vector<string> inconsistencies;

    // Check for circular implications
    for (const auto& rule1Pair : rules) 
    {
        const Rule& rule1 = rule1Pair.second;

        for (const auto& rule2Pair : rules)
        {
            const Rule& rule2 = rule2Pair.second;

            if (rule1.ruleId != rule2.ruleId)
            {
                // Check for circular: (P → Q) and (Q → P)
                if (rule1.condition == rule2.consequence && rule1.consequence == rule2.condition)
                {

                    if (factExists(rule1.condition) && factExists(rule1.consequence)) 
                    {
                        bool p = getFact(rule1.condition);
                        bool q = getFact(rule1.consequence);

                        if (p != q) 
                        {
                            inconsistencies.push_back("Circular implication between " + rule1.condition + " and " + rule1.consequence);
                        }
                    }
                }
            }
        }
    }

    return inconsistencies;
}

void LogicEngine::displayConflicts() const
{
    cout << "\n========== CONFLICTS DETECTED ==========\n";
    cout << "Total Conflicts: " << conflicts.size() << "\n\n";

    if (conflicts.empty())
    {
        cout << " No conflicts found.\n";
    }
    else {
        for (size_t i = 0; i < conflicts.size(); i++)
        {
            cout << "Conflict " << (i + 1) << ":\n";
            conflicts[i].display();
            cout << "\n";
        }
    }

    cout << "========================================\n";
}

bool LogicEngine::verifyPolicy(string policyRule) 
{
    Rule rule = parseNaturalLanguageRule(policyRule);

    if (factExists(rule.condition))
    {
        bool conditionTrue = getFact(rule.condition);

        if (conditionTrue)
        {
            if (factExists(rule.consequence))
            {
                return getFact(rule.consequence);
            }
            else 
            {
                return false;
            }
        }
    }

    return true;
}

bool LogicEngine::isRuleSatisfied(string ruleId)
{
    if (rules.find(ruleId) == rules.end())
    {
        return false;
    }

    const Rule& rule = rules[ruleId];

    if (factExists(rule.condition)) 
    {
        bool conditionTrue = getFact(rule.condition);

        if (conditionTrue) 
        {
            if (factExists(rule.consequence))
            {
                return 
                    getFact(rule.consequence);
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

vector<string> LogicEngine::getViolatedPolicies()
{
    vector<string> violations;

    for (const auto& rulePair : rules) 
    {
        const Rule& rule = rulePair.second;
        if (!isRuleSatisfied(rule.ruleId)) 
        {
            violations.push_back(rule.ruleId + ": IF " + rule.condition + " THEN " + rule.consequence);
        }
    }

    return violations;
}

bool LogicEngine::evaluateExpression(string expression) 
{
    expression = trim(expression);
    if (expression.find(" AND ") != string::npos) 
    {
        auto pos = expression.find(" AND ");
        string left = expression.substr(0, pos);
        string right = expression.substr(pos + 5);

        return evaluateExpression(left) && evaluateExpression(right);
    }
    else if (expression.find(" OR ") != string::npos)
    {
        auto pos = expression.find(" OR ");
        string left = expression.substr(0, pos);
        string right = expression.substr(pos + 4);

        return evaluateExpression(left) || evaluateExpression(right);
    }
    else if (expression.find("NOT ") == 0) 
    {
        string stmt = expression.substr(4);
        return !evaluateExpression(stmt);
    }
    else 
    {
        return getFact(expression);
    }
}

bool LogicEngine::isTautology(string expression) 
{
    vector<string> variables = extractVariables(expression);
    int n = variables.size();

    if (n == 0) 
        return evaluateExpression(expression);
    if (n > 10)
    {
        cout << "Warning: Too many variables for exhaustive check\n";
        return false;
    }

    int combinations = 1 << n;

    for (int i = 0; i < combinations; i++) 
    {
        // Set truth values
        for (int j = 0; j < n; j++)
        {
            bool value = (i & (1 << j)) != 0;
            addFact(variables[j], value);
        }

        if (!evaluateExpression(expression)) 
        {
            return false;
        }
    }

    return true;
}

bool LogicEngine::isContradiction(string expression)
{
    vector<string> variables = extractVariables(expression);
    int n = variables.size();
    if (n == 0)
        return !evaluateExpression(expression);
    if (n > 10) 
    {
        cout << "Warning: Too many variables for exhaustive check\n";
        return false;
    }

    int combinations = 1 << n;

    for (int i = 0; i < combinations; i++)
    {
        for (int j = 0; j < n; j++) {
            bool value = (i & (1 << j)) != 0;
            addFact(variables[j], value);
        }

        if (evaluateExpression(expression))
        {
            return false;
        }
    }

    return true;
}

void LogicEngine::displayTruthTable(string expression, vector<string> variables) 
{
    cout << "\n========== TRUTH TABLE ==========\n";
    cout << "Expression: " << expression << "\n\n";

    if (variables.empty())
    {
        variables = extractVariables(expression);
    }

    int n = variables.size();

    if (n > 8) 
    {
        cout << "Error: Too many variables (max 8 for display)\n";
        return;
    }

    // Print header
    for (const string& var : variables) 
    {
        cout << var << "\t";
    }
    cout << "| Result\n";
    cout << string(n * 8 + 10, '-') << "\n";

    int combinations = 1 << n;

    for (int i = 0; i < combinations; i++)
    {
        // Set values and print
        for (int j = 0; j < n; j++) 
        {
            bool value = (i & (1 << j)) != 0;
            cout << (value ? "T" : "F") << "\t";
            addFact(variables[j], value);
        }

        bool result = evaluateExpression(expression);
        cout << "| " << (result ? "T" : "F") << "\n";
    }

    cout << "=================================\n";
}

void LogicEngine::displayStatistics() const 
{
    cout << "\n========== LOGIC ENGINE STATISTICS ==========\n";
    cout << "Total Rules: " << rules.size() << "\n";

    int activeRules = 0;
    for (const auto& pair : rules) 
    {
        if (pair.second.isActive) 
            activeRules++;
    }
    cout << "Active Rules: " << activeRules << "\n";
    cout << "Inactive Rules: " << (rules.size() - activeRules) << "\n";

    cout << "\nTotal Facts: " << facts.size() << "\n";

    int trueFacts = 0;
    for (const auto& pair : facts)
    {
        if (pair.second.truthValue) 
            trueFacts++;
    }
    cout << "True Facts: " << trueFacts << "\n";
    cout << "False Facts: " << (facts.size() - trueFacts) << "\n";

    cout << "\nTotal Conflicts: " << conflicts.size() << "\n";

    cout << "=============================================\n";
}

vector<string> LogicEngine::parseComponents(string statement)
{
    vector<string> components;
    stringstream ss(statement);
    string word;

    while (ss >> word)
    {
        components.push_back(word);
    }

    return components;
}

vector<string> LogicEngine::extractVariables(string expression)
{
    set<string> uniqueVars;
    string current = "";
    for (size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        if (c == ' ' || c == '(' || c == ')')
        {
            if (!current.empty()) 
            {
                if (current != "AND" && current != "OR" && current != "NOT") 
                {
                    uniqueVars.insert(current);
                }
                current = "";
            }
        }
        else
        {
            current += c;
        }
    }

    if (!current.empty() && current != "AND" && current != "OR" && current != "NOT")
    {
        uniqueVars.insert(current);
    }

    return vector<string>(uniqueVars.begin(), uniqueVars.end());
}

bool LogicEngine::areEquivalent(string stmt1, string stmt2)
{
    vector<string> vars1 = extractVariables(stmt1);
    vector<string> vars2 = extractVariables(stmt2);

    set<string> allVars(vars1.begin(), vars1.end());
    allVars.insert(vars2.begin(), vars2.end());

    vector<string> variables(allVars.begin(), allVars.end());
    int n = variables.size();

    if (n > 10)
        return false;

    int combinations = 1 << n;

    for (int i = 0; i < combinations; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            bool value = (i & (1 << j)) != 0;
            addFact(variables[j], value);
        }

        bool result1 = evaluateExpression(stmt1);
        bool result2 = evaluateExpression(stmt2);

        if (result1 != result2) 
        {
            return false;
        }
    }

    return true;
}

string LogicEngine::trim(const string& str)
{
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";

    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}