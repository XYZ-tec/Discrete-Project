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

string DataBase::trim(const string& str) const
{
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";
    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

//  LOAD FUNCTIONS 

bool DataBase::loadStudentsFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header line if present
    getline(file, line);
    if (line.find("StudentID") == string::npos)
    {
        // No header, rewind
        file.clear();
        file.seekg(0);
    }

    // Format: StudentID,Name,Department,Year,CompletedCourses(separated by semicolons)
    // Example: S001,John Doe,CS,2,CS101;MATH101;PHY101
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, name, dept, yearStr, completedStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dept, ',');
        getline(ss, yearStr, ',');
        getline(ss, completedStr);

        id = trim(id);
        name = trim(name);
        dept = trim(dept);
        yearStr = trim(yearStr);
        completedStr = trim(completedStr);

        int year = stoi(yearStr);
        Student student(id, name, dept, year);

        // Parse completed courses
        if (!completedStr.empty())
        {
            stringstream courseStream(completedStr);
            string courseId;
            while (getline(courseStream, courseId, ';'))
            {
                courseId = trim(courseId);
                if (!courseId.empty())
                {
                    student.addCompletedCourse(courseId);
                }
            }
        }

        students[id] = student;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " students from " << filename << endl;
    return true;
}

bool DataBase::loadCoursesFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("CourseID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: CourseID,Name,Credits,Prerequisites(separated by semicolons)
    // Example: CS201,Data Structures,3,CS101;MATH101
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, name, creditsStr, prereqStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, creditsStr, ',');
        getline(ss, prereqStr);

        id = trim(id);
        name = trim(name);
        creditsStr = trim(creditsStr);
        prereqStr = trim(prereqStr);

        int credits = stoi(creditsStr);
        Courses course(id, name, credits);

        // Parse prerequisites
        if (!prereqStr.empty())
        {
            stringstream prereqStream(prereqStr);
            string prereqId;
            while (getline(prereqStream, prereqId, ';'))
            {
                prereqId = trim(prereqId);
                if (!prereqId.empty())
                {
                    course.addPrerequisite(prereqId);
                }
            }
        }

        courses[id] = course;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " courses from " << filename << endl;
    return true;
}

bool DataBase::loadFacultyFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("FacultyID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: FacultyID,Name,Department,AssignedCourses(separated by semicolons)
    // Example: F001,Dr. Smith,CS,CS101;CS201
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, name, dept, coursesStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, dept, ',');
        getline(ss, coursesStr);

        id = trim(id);
        name = trim(name);
        dept = trim(dept);
        coursesStr = trim(coursesStr);

        Faculty faculty(id, name, dept);

        // Parse assigned courses
        if (!coursesStr.empty())
        {
            stringstream courseStream(coursesStr);
            string courseId;
            while (getline(courseStream, courseId, ';'))
            {
                courseId = trim(courseId);
                if (!courseId.empty())
                {
                    faculty.assignCourse(courseId);
                }
            }
        }

        faculties[id] = faculty;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " faculty members from " << filename << endl;
    return true;
}

bool DataBase::loadRoomsFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("RoomID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: RoomID,Type,Capacity
    // Example: R101,Lecture,50
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, type, capacityStr;

        getline(ss, id, ',');
        getline(ss, type, ',');
        getline(ss, capacityStr);

        id = trim(id);
        type = trim(type);
        capacityStr = trim(capacityStr);

        int capacity = stoi(capacityStr);
        Rooms room(id, type, capacity);

        rooms[id] = room;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " rooms from " << filename << endl;
    return true;
}

bool DataBase::loadTimeSlotsFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("TimeSlotID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: TimeSlotID,Day,StartTime,EndTime
    // Example: T001,Monday,09:00,10:30
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, day, startTime, endTime;

        getline(ss, id, ',');
        getline(ss, day, ',');
        getline(ss, startTime, ',');
        getline(ss, endTime);

        id = trim(id);
        day = trim(day);
        startTime = trim(startTime);
        endTime = trim(endTime);

        TimeSlots timeSlot(id, day, startTime, endTime);
        timeSlots[id] = timeSlot;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " time slots from " << filename << endl;
    return true;
}

bool DataBase::loadEnrollmentsFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("StudentID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: StudentID,CourseID,TimeSlotID,SemesterID
    // Example: S001,CS101,T001,SEM001
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string studentId, courseId, timeSlotId, semesterId;

        getline(ss, studentId, ',');
        getline(ss, courseId, ',');
        getline(ss, timeSlotId, ',');
        getline(ss, semesterId);

        studentId = trim(studentId);
        courseId = trim(courseId);
        timeSlotId = trim(timeSlotId);
        semesterId = trim(semesterId);

        Enrollment enrollment(studentId, courseId, timeSlotId, semesterId);
        enrollments.push_back(enrollment);
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " enrollments from " << filename << endl;
    return true;
}

bool DataBase::loadDepartmentsFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("DepartmentID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: DepartmentID,Name,StudentIDs(separated by semicolons)
    // Example: D001,Computer Science,S001;S002;S003
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, name, studentIdsStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, studentIdsStr);

        id = trim(id);
        name = trim(name);
        studentIdsStr = trim(studentIdsStr);

        Department department(id, name);

        // Parse student IDs
        if (!studentIdsStr.empty())
        {
            stringstream studentStream(studentIdsStr);
            string studentId;
            while (getline(studentStream, studentId, ';'))
            {
                studentId = trim(studentId);
                if (!studentId.empty())
                {
                    department.addStudent(studentId);
                }
            }
        }

        departments[id] = department;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " departments from " << filename << endl;
    return true;
}

bool DataBase::loadSemestersFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    int loadedCount = 0;

    // Skip header
    getline(file, line);
    if (line.find("SemesterID") == string::npos)
    {
        file.clear();
        file.seekg(0);
    }

    // Format: SemesterID,Name,StartDate,EndDate
    // Example: SEM001,Fall 2024,2024-08-15,2024-12-15
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string id, name, startDate, endDate;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, startDate, ',');
        getline(ss, endDate);

        id = trim(id);
        name = trim(name);
        startDate = trim(startDate);
        endDate = trim(endDate);

        Semester semester(id, name, startDate, endDate);
        semesters[id] = semester;
        loadedCount++;
    }

    file.close();
    cout << " Loaded " << loadedCount << " semesters from " << filename << endl;
    return true;
}

//  SAVE FUNCTIONS 

bool DataBase::saveStudentsToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    // Write header
    file << "# Students Database File\n";
    file << "# Format: StudentID,Name,Department,Year,CompletedCourses\n\n";
    file << "StudentID,Name,Department,Year,CompletedCourses\n";

    for (const auto& pair : students)
    {
        const Student& s = pair.second;
        file << s.getId() << ","
            << s.getName() << ","
            << s.getDepartment() << ","
            << s.getYear() << ",";

        // Write completed courses
        const vector<string>& completed = s.getCompletedCourses();
        for (size_t i = 0; i < completed.size(); i++)
        {
            file << completed[i];
            if (i < completed.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    file.close();
    cout << " Saved " << students.size() << " students to " << filename << endl;
    return true;
}

bool DataBase::saveCoursesToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Courses Database File\n";
    file << "# Format: CourseID,Name,Credits,Prerequisites\n\n";
    file << "CourseID,Name,Credits,Prerequisites\n";

    for (const auto& pair : courses)
    {
        const Courses& c = pair.second;
        file << c.getId() << ","
            << c.getName() << ","
            << c.getCredits() << ",";

        const vector<string>& prereqs = c.getPrerequisites();
        for (size_t i = 0; i < prereqs.size(); i++)
        {
            file << prereqs[i];
            if (i < prereqs.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    file.close();
    cout << " Saved " << courses.size() << " courses to " << filename << endl;
    return true;
}

bool DataBase::saveFacultyToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Faculty Database File\n";
    file << "# Format: FacultyID,Name,Department,AssignedCourses\n\n";
    file << "FacultyID,Name,Department,AssignedCourses\n";

    for (const auto& pair : faculties)
    {
        const Faculty& f = pair.second;
        file << f.getId() << ","
            << f.getName() << ","
            << f.getDepartment() << ",";

        const vector<string>& courses = f.getAssignedCourses();
        for (size_t i = 0; i < courses.size(); i++)
        {
            file << courses[i];
            if (i < courses.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    file.close();
    cout << " Saved " << faculties.size() << " faculty members to " << filename << endl;
    return true;
}

bool DataBase::saveRoomsToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Rooms Database File\n";
    file << "# Format: RoomID,Type,Capacity\n\n";
    file << "RoomID,Type,Capacity\n";

    for (const auto& pair : rooms)
    {
        const Rooms& r = pair.second;
        file << r.getId() << ","
            << r.getType() << ","
            << r.getCapacity() << "\n";
    }

    file.close();
    cout << " Saved " << rooms.size() << " rooms to " << filename << endl;
    return true;
}

bool DataBase::saveTimeSlotsToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Time Slots Database File\n";
    file << "# Format: TimeSlotID,Day,StartTime,EndTime\n\n";
    file << "TimeSlotID,Day,StartTime,EndTime\n";

    for (const auto& pair : timeSlots)
    {
        const TimeSlots& t = pair.second;
        file << t.getId() << ","
            << t.getDay() << ","
            << t.getStartTime() << ","
            << t.getEndTime() << "\n";
    }

    file.close();
    cout << " Saved " << timeSlots.size() << " time slots to " << filename << endl;
    return true;
}

bool DataBase::saveEnrollmentsToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Enrollments Database File\n";
    file << "# Format: StudentID,CourseID,TimeSlotID,SemesterID\n\n";
    file << "StudentID,CourseID,TimeSlotID,SemesterID\n";

    for (const Enrollment& e : enrollments)
    {
        file << e.getStudentId() << ","
            << e.getCourseId() << ","
            << e.getTimeSlotId() << ","
            << e.getSemesterId() << "\n";
    }

    file.close();
    cout << " Saved " << enrollments.size() << " enrollments to " << filename << endl;
    return true;
}

bool DataBase::saveDepartmentsToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Departments Database File\n";
    file << "# Format: DepartmentID,Name,StudentIDs\n\n";
    file << "DepartmentID,Name,StudentIDs\n";

    for (const auto& pair : departments)
    {
        const Department& d = pair.second;
        file << d.getId() << ","
            << d.getName() << ",";

        const vector<string>& students = d.getStudents();
        for (size_t i = 0; i < students.size(); i++)
        {
            file << students[i];
            if (i < students.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    file.close();
    cout << " Saved " << departments.size() << " departments to " << filename << endl;
    return true;
}

bool DataBase::saveSemestersToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot create file " << filename << endl;
        return false;
    }

    file << "# Semesters Database File\n";
    file << "# Format: SemesterID,Name,StartDate,EndDate\n\n";
    file << "SemesterID,Name,StartDate,EndDate\n";

    for (const auto& pair : semesters)
    {
        const Semester& s = pair.second;
        file << s.getId() << ","
            << s.getName() << ","
            << s.getStartDate() << ","
            << s.getEndDate() << "\n";
    }

    file.close();
    cout << " Saved " << semesters.size() << " semesters to " << filename << endl;
    return true;
}

//  BULK LOAD/SAVE

bool DataBase::loadAllData(string directory)
{
    cout << "\n========== LOADING ALL DATA ==========\n";

    bool allSuccess = true;

    allSuccess &= loadStudentsFromFile(directory + "/students.txt");
    allSuccess &= loadCoursesFromFile(directory + "/courses.txt");
    allSuccess &= loadFacultyFromFile(directory + "/faculty.txt");
    allSuccess &= loadRoomsFromFile(directory + "/rooms.txt");
    allSuccess &= loadTimeSlotsFromFile(directory + "/timeslots.txt");
    allSuccess &= loadEnrollmentsFromFile(directory + "/enrollments.txt");
    allSuccess &= loadDepartmentsFromFile(directory + "/departments.txt");
    allSuccess &= loadSemestersFromFile(directory + "/semesters.txt");

    if (allSuccess)
    {
        cout << "\n All data loaded successfully!" << endl;
        buildPrerequisiteGraph();
        cout << " Prerequisite graph built." << endl;
    }
    else
    {
        cout << "\n Some files could not be loaded." << endl;
    }

    cout << "======================================\n\n";
    return allSuccess;
}

bool DataBase::saveAllData(string directory) const
{
    cout << "\n========== SAVING ALL DATA ==========\n";

    bool allSuccess = true;

    allSuccess &= saveStudentsToFile(directory + "/students.txt");
    allSuccess &= saveCoursesToFile(directory + "/courses.txt");
    allSuccess &= saveFacultyToFile(directory + "/faculty.txt");
    allSuccess &= saveRoomsToFile(directory + "/rooms.txt");
    allSuccess &= saveTimeSlotsToFile(directory + "/timeslots.txt");
    allSuccess &= saveEnrollmentsToFile(directory + "/enrollments.txt");
    allSuccess &= saveDepartmentsToFile(directory + "/departments.txt");
    allSuccess &= saveSemestersToFile(directory + "/semesters.txt");

    if (allSuccess)
    {
        cout << "\n All data saved successfully to " << directory << "/" << endl;
    }
    else
    {
        cout << "\n Some files could not be saved." << endl;
    }

    cout << "=====================================\n\n";
    return allSuccess;
}