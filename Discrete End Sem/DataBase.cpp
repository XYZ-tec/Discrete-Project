#include "DataBase.h"
// Add methods
void DataBase::addStudent(const Student& s)
{
    students[s.getId()] = s;
}

void DataBase::addCourse(const Courses& c) 
{
    courses[c.getId()] = c;
}

void DataBase::addFaculty(const Faculty& f) 
{
    faculties[f.getId()] = f;
}

void DataBase::addRoom(const Rooms& r) 
{
    rooms[r.getId()] = r;
}

void DataBase::addTimeSlot(const TimeSlots& t) 
{
    timeSlots[t.getId()] = t;
}

void DataBase::addEnrollment(const Enrollment& e) 
{
    enrollments.push_back(e);
}

void DataBase::addTranscript(const Transcript& t) 
{
    transcripts[t.getStudentId()] = t;
}

void DataBase::addDepartment(const Department& d) 
{
    departments[d.getId()] = d;
}

void DataBase::addSemester(const Semester& s)
{
    semesters[s.getId()] = s;
}

// Get methods
Student* DataBase::getStudent(string id)
{
    if (students.find(id) != students.end()) 
    {
        return &students[id];
    }
    return nullptr;
}

Courses* DataBase::getCourse(string id) 
{
    if (courses.find(id) != courses.end()) 
    {
        return &courses[id];
    }
    return nullptr;
}

Faculty* DataBase::getFaculty(string id)
{
    if (faculties.find(id) != faculties.end()) 
    {
        return &faculties[id];
    }
    return nullptr;
}

Rooms* DataBase::getRoom(string id)
{
    if (rooms.find(id) != rooms.end()) 
    {
        return &rooms[id];
    }
    return nullptr;
}

TimeSlots* DataBase::getTimeSlot(string id) 
{
    if (timeSlots.find(id) != timeSlots.end()) 
    {
        return &timeSlots[id];
    }
    return nullptr;
}

Department* DataBase::getDepartment(string id) 
{
    if (departments.find(id) != departments.end())
    {
        return &departments[id];
    }
    return nullptr;
}

Semester* DataBase::getSemester(string id)
{
    if (semesters.find(id) != semesters.end())
    {
        return &semesters[id];
    }
    return nullptr;
}

// Display methods
void DataBase::displayAllStudents() const
{
    cout << "===== All Students =====" << endl;
    for (const auto& pair : students) 
    {
        pair.second.display();
        cout << "------------------------" << endl;
    }
}

void DataBase::displayAllCourses() const
{
    cout << "===== All Courses =====" << endl;
    for (const auto& pair : courses) 
    {
        pair.second.display();
        cout << "------------------------" << endl;
    }
}

void DataBase::displayAllFaculty() const
{
    cout << "===== All Faculty =====" << endl;
    for (const auto& pair : faculties) 
    {
        pair.second.display();
        cout << "------------------------" << endl;
    }
}

// Build prerequisite graph
void DataBase::buildPrerequisiteGraph()
{
    prerequisiteGraph.clear();
    for (const auto& pair : courses)
    {
        string courseId = pair.first;
        const vector<string>& prereqs = pair.second.getPrerequisites();
        prerequisiteGraph[courseId] = prereqs;
    }
}

// Check if student can enroll in a course
bool DataBase::canEnroll(string studentId, string courseId) 
{
    Student* student = getStudent(studentId);
    Courses* course = getCourse(courseId);

    if (!student || !course) 
    {
        return false;
    }

    // Check all prerequisites
    const vector<string>& prereqs = course->getPrerequisites();
    for (const string& prereq : prereqs) 
    {
        if (!student->hasCompletedCourse(prereq)) 
        {
            return false;
        }
    }

    return true;
}

// Get available courses for a student
vector<string> DataBase::getAvailableCourses(string studentId) 
{
    vector<string> available;
    Student* student = getStudent(studentId);

    if (!student) 
    {
        return available;
    }

    for (const auto& pair : courses) 
    {
        string courseId = pair.first;
        if (canEnroll(studentId, courseId) && !student->hasCompletedCourse(courseId))
        {
            available.push_back(courseId);
        }
    }

    return available;
}
bool hasCycleDFSHelper(const string& courseId, set<string>& visited, set<string>& recursionStack, const map<string, vector<string>>& prereqGraph) 
{
    visited.insert(courseId);
    recursionStack.insert(courseId);

    if (prereqGraph.find(courseId) != prereqGraph.end()) 
    {
        const vector<string>& prereqs = prereqGraph.at(courseId);
        for (const string& prereq : prereqs) 
        {
            // If not visited, recurse
            if (visited.find(prereq) == visited.end())
            {
                if (hasCycleDFSHelper(prereq, visited, recursionStack, prereqGraph)) 
                {
                    return true;
                }
            }
            // If in recursion stack, cycle found
            else if (recursionStack.find(prereq) != recursionStack.end())
            {
                return true;
            }
        }
    }

    recursionStack.erase(courseId);
    return false;
}
// Check for circular dependencies using DFS
bool DataBase::hasCircularDependency()
{
    set<string> visited;
    set<string> recursionStack;
    // Check each course
    for (const auto& pair : courses) 
    {
        if (visited.find(pair.first) == visited.end()) 
        {
            if (hasCycleDFSHelper(pair.first, visited, recursionStack, prerequisiteGraph))
            {
                return true;
            }
        }
    }
    return false;
}


// Get valid course sequence using topological sort
vector<string> DataBase::getValidCourseSequence()
{
    vector<string> sequence;
    map<string, int> inDegree;
    queue<string> q;

    // Calculate in-degrees
    for (const auto& pair : courses) 
    {
        inDegree[pair.first] = 0;
    }

    for (const auto& pair : prerequisiteGraph)
    {
        for (const string& prereq : pair.second) 
        {
            inDegree[pair.first]++;
        }
    }

    // Add courses with no prerequisites to queue
    for (const auto& pair : inDegree)
    {
        if (pair.second == 0)
        {
            q.push(pair.first);
        }
    }

    // Process queue
    while (!q.empty())
    {
        string current = q.front();
        q.pop();
        sequence.push_back(current);

        // Reduce in-degree for courses that depend on current
        for (const auto& pair : prerequisiteGraph) {
            for (const string& prereq : pair.second) {
                if (prereq == current) {
                    inDegree[pair.first]--;
                    if (inDegree[pair.first] == 0) {
                        q.push(pair.first);
                    }
                }
            }
        }
    }

    return sequence;
}

// Get all prerequisites for a course (transitive closure)
set<string> DataBase::getAllPrerequisites(string courseId) 
{
    set<string> allPrereqs;
    queue<string> toProcess;
    Courses* course = getCourse(courseId);
    if (!course) 
    {
        return allPrereqs;
    }

    // Start with direct prerequisites 
    const vector<string>& directPrereqs = course->getPrerequisites();
    for (const string& prereq : directPrereqs) 
    {
        toProcess.push(prereq);
        allPrereqs.insert(prereq);
    }

    // BFS to get transitive prerequisites
    while (!toProcess.empty()) 
    {
        string current = toProcess.front();
        toProcess.pop();

        Courses* currentCourse = getCourse(current);
        if (currentCourse)
        {
            const vector<string>& prereqs = currentCourse->getPrerequisites();
            for (const string& prereq : prereqs)
            {
                if (allPrereqs.find(prereq) == allPrereqs.end())
                {
                    allPrereqs.insert(prereq);
                    toProcess.push(prereq);
                }
            }
        }
    }

    return allPrereqs;
}

// Check for time conflicts
bool DataBase::hasTimeConflict(string studentId, string courseId, string timeSlotId)
{
    TimeSlots* newSlot = getTimeSlot(timeSlotId);
    if (!newSlot)
    {
        return false;
    }

    // Check student's current enrollments
    for (const Enrollment& e : enrollments) 
    {
        if (e.getStudentId() == studentId)
        {
            TimeSlots* existingSlot = getTimeSlot(e.getTimeSlotId());
            if (existingSlot && existingSlot->overlaps(*newSlot)) 
            {
                return true;
            }
        }
    }

    return false;
}

// Check for faculty conflicts
bool DataBase::hasFacultyConflict(string facultyId, string timeSlotId)
{
    TimeSlots* newSlot = getTimeSlot(timeSlotId);
    if (!newSlot)
    {
        return false;
    }

    Faculty* faculty = getFaculty(facultyId);
    if (!faculty)
    {
        return false;
    }

    // Check all assigned courses
    const vector<string>& assignedCourses = faculty->getAssignedCourses();
    for (const string& courseId : assignedCourses) 
    {
        for (const Enrollment& e : enrollments)
        {
            if (e.getCourseId() == courseId)
            {
                TimeSlots* existingSlot = getTimeSlot(e.getTimeSlotId());
                if (existingSlot && existingSlot->overlaps(*newSlot)) 
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Get enrolled students for a course
vector<string> DataBase::getEnrolledStudents(string courseId) 
{
    vector<string> enrolledStudents;
    for (const Enrollment& e : enrollments)
    {
        if (e.getCourseId() == courseId) 
        {
            enrolledStudents.push_back(e.getStudentId());
        }
    }
    return enrolledStudents;
}

// Get courses for a student
vector<string> DataBase::getStudentCourses(string studentId)   
{
    vector<string> studentCourses;
    for (const Enrollment& e : enrollments) 
    {
        if (e.getStudentId() == studentId) 
{
            studentCourses.push_back(e.getCourseId());
        }
    }
    return studentCourses;
}