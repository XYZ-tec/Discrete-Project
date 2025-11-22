#include "FunctionsModule.h"

bool FunctionsModule::isValidFunction(const Function& func, const set<string>& domain)
{
    for (const string& element : domain)
    {
        if (func.find(element) == func.end())
        {
            return false;
        }
    }
    return true;
}

bool FunctionsModule::isInjective(const Function& func)
{
    set<string> usedValues;
    for (const auto& pair : func)
    {
        if (usedValues.find(pair.second) != usedValues.end())
        {
            return false; // Same output for different inputs
        }
        usedValues.insert(pair.second);
    }
    return true;
}

bool FunctionsModule::isSurjective(const Function& func, const set<string>& codomain)
{
    set<string> image = getImage(func);
    for (const string& element : codomain)
    {
        if (image.find(element) == image.end())
        {
            return false;
        }
    }
    return true;
}

bool FunctionsModule::isBijective(const Function& func, const set<string>& codomain)
{
    return isInjective(func) && isSurjective(func, codomain);
}

FunctionsModule::Function FunctionsModule::composeFunctions(const Function& f, const Function& g)
{
    Function result;
    for (const auto& pair : f)
    {
        string input = pair.first;
        string intermediate = pair.second;

        if (g.find(intermediate) != g.end())
        {
            string output = g.at(intermediate);
            result[input] = output;
        }
    }
    return result;
}

FunctionsModule::Function FunctionsModule::inverseFunction(const Function& func)
{
    Function inverse;

    if (!isInjective(func))
    {
        cout << "Warning: Function is not injective, inverse may not be valid!" << endl;
    }

    for (const auto& pair : func)
    {
        inverse[pair.second] = pair.first;
    }

    return inverse;
}

set<string> FunctionsModule::getImage(const Function& func)
{
    set<string> image;
    for (const auto& pair : func)
    {
        image.insert(pair.second);
    }
    return image;
}

set<string> FunctionsModule::getDomain(const Function& func)
{
    set<string> domain;
    for (const auto& pair : func)
    {
        domain.insert(pair.first);
    }
    return domain;
}

set<string> FunctionsModule::getPreimage(const Function& func, const string& element)
{
    set<string> preimage;
    for (const auto& pair : func)
    {
        if (pair.second == element)
        {
            preimage.insert(pair.first);
        }
    }
    return preimage;
}

void FunctionsModule::displayFunction(const Function& func, const string& functionName)
{
    cout << functionName << " = { ";
    bool first = true;
    for (const auto& pair : func)
    {
        if (!first) cout << ", ";
        cout << pair.first << " → " << pair.second;
        first = false;
    }
    cout << " }" << endl;
    cout << "Domain size: " << func.size() << endl;
    cout << "Image size: " << getImage(func).size() << endl;
}

void FunctionsModule::displayProperties(const Function& func, const set<string>& codomain, const string& functionName)
{
    cout << "\n========== Properties of " << functionName << " ==========\n";
    cout << "Domain size: " << func.size() << endl;
    cout << "Codomain size: " << codomain.size() << endl;
    cout << "Image size: " << getImage(func).size() << endl;
    cout << "Injective (One-to-One): " << (isInjective(func) ? "Yes" : "No") << endl;
    cout << "Surjective (Onto): " << (isSurjective(func, codomain) ? "Yes" : "No") << endl;
    cout << "Bijective (One-to-One and Onto): " << (isBijective(func, codomain) ? "Yes" : "No") << endl;
    cout << "Constant: " << (isConstantFunction(func) ? "Yes" : "No") << endl;
    cout << "==================================================\n";
}

bool FunctionsModule::isIdentityFunction(const Function& func, const set<string>& domain)
{
    for (const string& element : domain)
    {
        if (func.find(element) == func.end() || func.at(element) != element)
        {
            return false;
        }
    }
    return true;
}

FunctionsModule::Function FunctionsModule::createIdentityFunction(const set<string>& domain)
{
    Function identity;
    for (const string& element : domain)
    {
        identity[element] = element;
    }
    return identity;
}

bool FunctionsModule::isConstantFunction(const Function& func)
{
    if (func.empty())
    {
        return false;
    }

    string firstValue = func.begin()->second;
    for (const auto& pair : func)
    {
        if (pair.second != firstValue)
        {
            return false;
        }
    }
    return true;
}

string FunctionsModule::applyFunction(const Function& func, const string& input)
{
    if (func.find(input) == func.end())
    {
        cout << "Error: Input not in function domain!" << endl;
        return "";
    }
    return func.at(input);
}

void FunctionsModule::demonstrateFunctions()
{
    cout << "\n========== FUNCTIONS MODULE DEMONSTRATION ==========\n";

    // Example 1: Course to Faculty Assignment (Injective)
    cout << "\n--- Example 1: Course → Faculty Assignment ---\n";
    Function courseToFaculty;
    courseToFaculty["CS101"] = "Dr. Smith";
    courseToFaculty["CS102"] = "Dr. Jones";
    courseToFaculty["Math101"] = "Dr. Brown";
    courseToFaculty["Math102"] = "Dr. Davis";

    set<string> facultyMembers = { "Dr. Smith", "Dr. Jones", "Dr. Brown", "Dr. Davis", "Dr. Wilson" };

    displayFunction(courseToFaculty, "Course→Faculty");
    displayProperties(courseToFaculty, facultyMembers, "Course→Faculty");

    // Example 2: Student to Department (Surjective)
    cout << "\n--- Example 2: Student → Department ---\n";
    Function studentToDept;
    studentToDept["S001"] = "CS";
    studentToDept["S002"] = "CS";
    studentToDept["S003"] = "Math";
    studentToDept["S004"] = "Physics";
    studentToDept["S005"] = "Math";

    set<string> departments = { "CS", "Math", "Physics" };

    displayFunction(studentToDept, "Student→Department");
    displayProperties(studentToDept, departments, "Student→Department");

    // Example 3: Room to Building (Bijective)
    cout << "\n--- Example 3: Room → Building (Bijective) ---\n";
    Function roomToBuilding;
    roomToBuilding["R101"] = "BuildingA";
    roomToBuilding["R102"] = "BuildingB";
    roomToBuilding["R103"] = "BuildingC";

    set<string> buildings = { "BuildingA", "BuildingB", "BuildingC" };

    displayFunction(roomToBuilding, "Room→Building");
    displayProperties(roomToBuilding, buildings, "Room→Building");

    // Get inverse
    cout << "\n--- Inverse Function ---\n";
    Function buildingToRoom = inverseFunction(roomToBuilding);
    displayFunction(buildingToRoom, "Building→Room (Inverse)");

    // Example 4: Function Composition
    cout << "\n--- Example 4: Function Composition ---\n";
    Function studentToCourse;
    studentToCourse["S001"] = "CS101";
    studentToCourse["S002"] = "CS102";
    studentToCourse["S003"] = "Math101";

    Function courseToRoom;
    courseToRoom["CS101"] = "Room101";
    courseToRoom["CS102"] = "Room102";
    courseToRoom["Math101"] = "Room103";

    displayFunction(studentToCourse, "Student→Course");
    displayFunction(courseToRoom, "Course→Room");

    Function studentToRoom = composeFunctions(studentToCourse, courseToRoom);
    displayFunction(studentToRoom, "Student→Room (Composition)");

    // Example 5: Identity Function
    cout << "\n--- Example 5: Identity Function ---\n";
    set<string> courseSet = { "CS101", "CS102", "Math101" };
    Function identity = createIdentityFunction(courseSet);
    displayFunction(identity, "Identity");
    cout << "Is Identity Function? " << (isIdentityFunction(identity, courseSet) ? "Yes" : "No") << endl;

    // Example 6: Constant Function
    cout << "\n--- Example 6: Constant Function ---\n";
    Function constant;
    constant["S001"] = "Freshman";
    constant["S002"] = "Freshman";
    constant["S003"] = "Freshman";

    displayFunction(constant, "Year Level");
    cout << "Is Constant Function? " << (isConstantFunction(constant) ? "Yes" : "No") << endl;

    // Example 7: Preimage
    cout << "\n--- Example 7: Preimage ---\n";
    set<string> csStudents = getPreimage(studentToDept, "CS");
    cout << "Students in CS Department (Preimage of 'CS'): { ";
    bool first = true;
    for (const string& s : csStudents)
    {
        if (!first) cout << ", ";
        cout << s;
        first = false;
    }
    cout << " }" << endl;
	cout << "==================================================\n";
}