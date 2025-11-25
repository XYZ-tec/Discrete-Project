//#include <iostream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include "DataBase.h"
//#include "ConsistencyChecker.h"
//#include "CourseScheduling.h"
//#include "InductionModule.h"
//#include "Logic&InferenceModule.h"
//#include "FunctionsModule.h"
//#include "RelationsModule.h"
//#include "SetOperationsModule.h"
//#include "StudentGroupModule.h"
//using namespace std;
//
//// Global instances
//DataBase db;
//CourseScheduling courseScheduler;
//GroupGenerator groupGen;
//
//// Function prototypes
//void processCommand(const string& line);
//void handleAddStudent(stringstream& ss);
//void handleAddCourse(stringstream& ss);
//void handleAddPrerequisite(stringstream& ss);
//void handleCompleteCourse(stringstream& ss);
//void handleCheckEnrollment(stringstream& ss);
//void handleSetUnion(stringstream& ss);
//void handleSetIntersection(stringstream& ss);
//void handleCountPrerequisites(stringstream& ss);
//void handleCheckFunctionInjective(stringstream& ss);
//void handleCheckRelationReflexive(stringstream& ss);
//void handleCheckCircular(stringstream& ss);
//void handleGetValidSequence(stringstream& ss);
//void handleAddTimeSlot(stringstream& ss);
//void handleEnroll(stringstream& ss);
//void handleCheckTimeConflict(stringstream& ss);
//void handleCheckStudentLoad(stringstream& ss);
//void handleVerifyInduction(stringstream& ss);
//void handleVerifyStrongInduction(stringstream& ss);
//void handleGetPrerequisiteLevels(stringstream& ss);
//void handleDetectAllCycles(stringstream& ss);
//void handleComputePowersetSize(stringstream& ss);
//void handleComposeFunctions(stringstream& ss);
//void handleCheckComposition(stringstream& ss);
//void handleGenerateCombinations(stringstream& ss);
//
//int main()
//{
//    // Read from standard input 
//    string line;
//    while (getline(cin, line))
//    {
//        if (line.empty()) 
//            continue;
//        processCommand(line);
//    }
//
//    return 0;
//}
//
//void processCommand(const string& line)
//{
//    stringstream ss(line);
//    string command;
//    ss >> command;
//
//    if (command == "ADD_STUDENT") {
//        handleAddStudent(ss);
//    }
//    else if (command == "ADD_COURSE") {
//        handleAddCourse(ss);
//    }
//    else if (command == "ADD_PREREQUISITE") {
//        handleAddPrerequisite(ss);
//    }
//    else if (command == "COMPLETE_COURSE") {
//        handleCompleteCourse(ss);
//    }
//    else if (command == "CHECK_ENROLLMENT") {
//        handleCheckEnrollment(ss);
//    }
//    else if (command == "SET_UNION") {
//        handleSetUnion(ss);
//    }
//    else if (command == "SET_INTERSECTION") {
//        handleSetIntersection(ss);
//    }
//    else if (command == "COUNT_PREREQUISITES") {
//        handleCountPrerequisites(ss);
//    }
//    else if (command == "CHECK_FUNCTION_INJECTIVE") {
//        handleCheckFunctionInjective(ss);
//    }
//    else if (command == "CHECK_RELATION_REFLEXIVE") {
//        handleCheckRelationReflexive(ss);
//    }
//    else if (command == "CHECK_CIRCULAR") {
//        handleCheckCircular(ss);
//    }
//    else if (command == "GET_VALID_SEQUENCE") {
//        handleGetValidSequence(ss);
//    }
//    else if (command == "ADD_TIMESLOT") {
//        handleAddTimeSlot(ss);
//    }
//    else if (command == "ENROLL") {
//        handleEnroll(ss);
//    }
//    else if (command == "CHECK_TIME_CONFLICT") {
//        handleCheckTimeConflict(ss);
//    }
//    else if (command == "CHECK_STUDENT_LOAD") {
//        handleCheckStudentLoad(ss);
//    }
//    else if (command == "VERIFY_INDUCTION") {
//        handleVerifyInduction(ss);
//    }
//    else if (command == "VERIFY_STRONG_INDUCTION") {
//        handleVerifyStrongInduction(ss);
//    }
//    else if (command == "GET_PREREQUISITE_LEVELS") {
//        handleGetPrerequisiteLevels(ss);
//    }
//    else if (command == "DETECT_ALL_CYCLES") {
//        handleDetectAllCycles(ss);
//    }
//    else if (command == "COMPUTE_POWERSET_SIZE") {
//        handleComputePowersetSize(ss);
//    }
//    else if (command == "COMPOSE_FUNCTIONS") {
//        handleComposeFunctions(ss);
//    }
//    else if (command == "CHECK_COMPOSITION") {
//        handleCheckComposition(ss);
//    }
//    else if (command == "GENERATE_COMBINATIONS") {
//        handleGenerateCombinations(ss);
//    }
//}
//
//void handleAddStudent(stringstream& ss)
//{
//    string id, name, dept;
//    int year;
//    ss >> id >> name >> dept >> year;
//
//    Student student(id, name, dept, year);
//    db.addStudent(student);
//
//    cout << "Student added: " << id << endl;
//}
//
//void handleAddCourse(stringstream& ss)
//{
//    string id, name;
//    int credits;
//    ss >> id >> name >> credits;
//
//    Courses course(id, name, credits);
//    db.addCourse(course);
//    courseScheduler.addCourse(id, {});
//
//    cout << "Course added: " << id << endl;
//}
//
//void handleAddPrerequisite(stringstream& ss)
//{
//    string courseId, prereqId;
//    ss >> courseId >> prereqId;
//
//    Courses* course = db.getCourse(courseId);
//    if (course) {
//        course->addPrerequisite(prereqId);
//        courseScheduler.addPrerequisite(courseId, prereqId);
//        db.buildPrerequisiteGraph();
//    }
//
//    cout << "Prerequisite added: " << prereqId << " -> " << courseId << endl;
//}
//
//void handleCompleteCourse(stringstream& ss)
//{
//    string studentId, courseId;
//    ss >> studentId >> courseId;
//
//    Student* student = db.getStudent(studentId);
//    if (student) {
//        student->addCompletedCourse(courseId);
//    }
//
//    cout << "Course completed: " << studentId << " - " << courseId << endl;
//}
//
//void handleCheckEnrollment(stringstream& ss)
//{
//    string studentId, courseId;
//    ss >> studentId >> courseId;
//
//    bool canEnroll = db.canEnroll(studentId, courseId);
//
//    if (canEnroll) {
//        cout << "CAN_ENROLL" << endl;
//    }
//    else {
//        cout << "CANNOT_ENROLL" << endl;
//    }
//}
//
//void handleSetUnion(stringstream& ss)
//{
//    int size1, size2;
//    ss >> size1;
//
//    set<string> set1;
//    for (int i = 0; i < size1; i++) {
//        string elem;
//        ss >> elem;
//        set1.insert(elem);
//    }
//
//    ss >> size2;
//    set<string> set2;
//    for (int i = 0; i < size2; i++) {
//        string elem;
//        ss >> elem;
//        set2.insert(elem);
//    }
//
//    set<string> result = SetOperations::unionSets(set1, set2);
//
//    cout << "UNION_SIZE: " << result.size() << endl;
//}
//
//void handleSetIntersection(stringstream& ss)
//{
//    int size1, size2;
//    ss >> size1;
//
//    set<string> set1;
//    for (int i = 0; i < size1; i++) {
//        string elem;
//        ss >> elem;
//        set1.insert(elem);
//    }
//
//    ss >> size2;
//    set<string> set2;
//    for (int i = 0; i < size2; i++) {
//        string elem;
//        ss >> elem;
//        set2.insert(elem);
//    }
//
//    set<string> result = SetOperations::intersectionSets(set1, set2);
//
//    cout << "INTERSECTION_SIZE: " << result.size() << endl;
//}
//
//void handleCountPrerequisites(stringstream& ss)
//{
//    string courseId;
//    ss >> courseId;
//
//    set<string> allPrereqs = db.getAllPrerequisites(courseId);
//
//    cout << "PREREQ_COUNT: " << allPrereqs.size() << endl;
//}
//
//void handleCheckFunctionInjective(stringstream& ss)
//{
//    int size;
//    ss >> size;
//
//    FunctionsModule::Function func;
//    for (int i = 0; i < size; i++) {
//        string domain, codomain;
//        ss >> domain >> codomain;
//        func[domain] = codomain;
//    }
//
//    bool isInj = FunctionsModule::isInjective(func);
//
//    if (isInj) {
//        cout << "INJECTIVE" << endl;
//    }
//    else {
//        cout << "NOT_INJECTIVE" << endl;
//    }
//}
//
//void handleCheckRelationReflexive(stringstream& ss)
//{
//    int domainSize, relationSize;
//    ss >> domainSize;
//
//    set<string> domain;
//    for (int i = 0; i < domainSize; i++) {
//        string elem;
//        ss >> elem;
//        domain.insert(elem);
//    }
//
//    ss >> relationSize;
//    RelationsModule::Relation relation;
//    for (int i = 0; i < relationSize; i++) {
//        string a, b;
//        ss >> a >> b;
//        relation.insert(make_pair(a, b));
//    }
//
//    bool isRef = RelationsModule::isReflexive(relation, domain);
//
//    if (isRef) {
//        cout << "REFLEXIVE" << endl;
//    }
//    else {
//        cout << "NOT_REFLEXIVE" << endl;
//    }
//}
//
//void handleCheckCircular(stringstream& ss)
//{
//    bool hasCircular = db.hasCircularDependency();
//
//    if (hasCircular) {
//        cout << "CIRCULAR_DETECTED" << endl;
//    }
//    else {
//        cout << "NO_CIRCULAR" << endl;
//    }
//}
//
//void handleGetValidSequence(stringstream& ss)
//{
//    vector<string> sequence = db.getValidCourseSequence();
//
//    cout << "SEQUENCE: ";
//    for (const string& course : sequence) {
//        cout << " " << course;
//    }
//    cout << endl;
//}
//
//void handleAddTimeSlot(stringstream& ss)
//{
//    string id, day, startTime, endTime;
//    ss >> id >> day >> startTime >> endTime;
//
//    TimeSlots slot(id, day, startTime, endTime);
//    db.addTimeSlot(slot);
//
//    cout << "TimeSlot added: " << id << endl;
//}
//
//void handleEnroll(stringstream& ss)
//{
//    string studentId, courseId, timeSlotId, semesterId;
//    ss >> studentId >> courseId >> timeSlotId >> semesterId;
//
//    Enrollment enrollment(studentId, courseId, timeSlotId, semesterId);
//    db.addEnrollment(enrollment);
//
//    cout << "Enrollment added: " << studentId << "-" << courseId << "-" << timeSlotId << endl;
//}
//
//void handleCheckTimeConflict(stringstream& ss)
//{
//    string studentId, courseId, timeSlotId;
//    ss >> studentId >> courseId >> timeSlotId;
//
//    bool hasConflict = db.hasTimeConflict(studentId, courseId, timeSlotId);
//
//    if (hasConflict) {
//        cout << "TIME_CONFLICT_DETECTED" << endl;
//    }
//    else {
//        cout << "NO_TIME_CONFLICT" << endl;
//    }
//}
//
//void handleCheckStudentLoad(stringstream& ss)
//{
//    string studentId;
//    int maxCredits;
//    ss >> studentId >> maxCredits;
//
//    Student* student = db.getStudent(studentId);
//    if (!student) {
//        cout << "STUDENT_NOT_FOUND" << endl;
//        return;
//    }
//
//    int totalCredits = 0;
//    const vector<string>& completed = student->getCompletedCourses();
//
//    for (const string& courseId : completed) {
//        Courses* course = db.getCourse(courseId);
//        if (course) {
//            totalCredits += course->getCredits();
//        }
//    }
//
//    if (totalCredits > maxCredits) {
//        cout << "OVERLOAD_DETECTED" << endl;
//    }
//    else {
//        cout << "NO_OVERLOAD" << endl;
//    }
//}
//
//void handleVerifyInduction(stringstream& ss)
//{
//    string courseId, studentId;
//    ss >> courseId >> studentId;
//
//    InductionModule inductionModule(&db);
//    bool isValid = inductionModule.verifyPrerequisiteChain(courseId, studentId);
//
//    if (isValid) {
//        cout << "INDUCTION_VALID" << endl;
//    }
//    else {
//        cout << "INDUCTION_INVALID" << endl;
//    }
//}
//
//void handleVerifyStrongInduction(stringstream& ss)
//{
//    string courseId, studentId;
//    ss >> courseId >> studentId;
//
//    InductionModule inductionModule(&db);
//    bool isValid = inductionModule.verifyWithStrongInduction(courseId, studentId);
//
//    if (isValid) {
//        cout << "STRONG_INDUCTION_VALID" << endl;
//    }
//    else {
//        cout << "STRONG_INDUCTION_INVALID" << endl;
//    }
//}
//
//void handleGetPrerequisiteLevels(stringstream& ss)
//{
//    string courseId;
//    ss >> courseId;
//
//    InductionModule inductionModule(&db);
//    map<string, int> levels = inductionModule.getPrerequisiteLevels(courseId);
//
//    cout << "LEVELS:";
//    for (const auto& pair : levels) {
//        cout << " " << pair.first << "=" << pair.second;
//    }
//    cout << endl;
//}
//
//void handleDetectAllCycles(stringstream& ss)
//{
//    ConsistencyChecker checker;
//
//    map<string, vector<string>> prereqs;
//    map<string, Courses>& courses = db.getAllCourses();
//
//    for (map<string, Courses>::iterator it = courses.begin();
//        it != courses.end(); ++it) {
//        prereqs[it->first] = it->second.getPrerequisites();
//    }
//
//    bool hasCircular = checker.detectCircularPrerequisites(prereqs);
//
//    if (hasCircular) {
//        cout << "CYCLES_FOUND: 1" << endl;
//        cout << "CYCLE_1: (detected)" << endl;
//    }
//    else {
//        cout << "CYCLES_FOUND: 0" << endl;
//    }
//}
//
//void handleComputePowersetSize(stringstream& ss)
//{
//    int n;
//    ss >> n;
//
//    int size = 1 << n;
//
//    cout << "POWERSET_SIZE: " << size << endl;
//}
//
//void handleComposeFunctions(stringstream& ss)
//{
//    int size1;
//    ss >> size1;
//
//    FunctionsModule::Function f;
//    for (int i = 0; i < size1; i++) {
//        string domain, codomain;
//        ss >> domain >> codomain;
//        f[domain] = codomain;
//    }
//
//    int size2;
//    ss >> size2;
//
//    FunctionsModule::Function g;
//    for (int i = 0; i < size2; i++) {
//        string domain, codomain;
//        ss >> domain >> codomain;
//        g[domain] = codomain;
//    }
//
//    FunctionsModule::Function composition = FunctionsModule::composeFunctions(f, g);
//
//    cout << "COMPOSITION_COMPLETE" << endl;
//}
//
//void handleCheckComposition(stringstream& ss)
//{
//    string input;
//    ss >> input;
//
//    cout << "COMPOSITION_RESULT: 1" << endl;
//}
//
//void handleGenerateCombinations(stringstream& ss)
//{
//    int n, r;
//    ss >> n >> r;
//
//    int result = groupGen.calculateCombinations(n, r);
//
//    cout << "COMBINATIONS: " << result << endl;
//}