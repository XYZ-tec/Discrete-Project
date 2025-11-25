#include "DataBase.h"
#include "ConsistencyChecker.h"
#include "courses.h"
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
    return checkPrerequisitesSatisfied(studentId, courseId);
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

bool DataBase::checkPrerequisitesSatisfied(string studentId, string courseId)
{
    Student* student = getStudent(studentId);
    Courses* course = getCourse(courseId);

    if (!student || !course)
        return false;

    const vector<string>& prereqs = course->getPrerequisites();
    for (const string& prereq : prereqs)
    {
        if (!student->hasCompletedCourse(prereq))
            return false;
    }

    return true;
}

bool DataBase::hasCircularDependency()
{
    ConsistencyChecker checker;

    // Build prerequisite map
    map<string, vector<string>> prereqMap;
    for (const auto& pair : courses)
    {
        prereqMap[pair.first] = pair.second.getPrerequisites();
    }

    return checker.detectCircularPrerequisites(prereqMap);
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

bool DataBase::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << " No existing data file. Starting fresh.\n";
        return false;
    }

    string line;
    string currentSection = "";

    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty()) continue;

        // Check for section headers
        if (line == "[STUDENTS]")
        {
            currentSection = "STUDENTS";
            continue;
        }
        else if (line == "[COURSES]")
        {
            currentSection = "COURSES";
            continue;
        }
        else if (line == "[FACULTY]")
        {
            currentSection = "FACULTY";
            continue;
        }
        else if (line == "[ROOMS]")
        {
            currentSection = "ROOMS";
            continue;
        }
        else if (line == "[TIMESLOTS]")
        {
            currentSection = "TIMESLOTS";
            continue;
        }
        else if (line == "[ENROLLMENTS]")
        {
            currentSection = "ENROLLMENTS";
            continue;
        }
        else if (line == "[DEPARTMENTS]")
        {
            currentSection = "DEPARTMENTS";
            continue;
        }
        else if (line == "[SEMESTERS]")
        {
            currentSection = "SEMESTERS";
            continue;
        }

        // Parse data based on current section
        if (currentSection == "STUDENTS")
        {
            // Format: ID|Name|Department|Year|Course1;Course2;Course3
            stringstream ss(line);
            string id, name, dept, yearStr, coursesStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, dept, '|');
            getline(ss, yearStr, '|');
            getline(ss, coursesStr);

            int year = stoi(yearStr);
            Student student(id, name, dept, year);

            // Parse completed courses
            if (!coursesStr.empty())
            {
                stringstream courseStream(coursesStr);
                string courseId;
                while (getline(courseStream, courseId, ';'))
                {
                    if (!courseId.empty())
                        student.addCompletedCourse(courseId);
                }
            }

            students[id] = student;
        }
        else if (currentSection == "COURSES")
        {
            // Format: ID|Name|Credits|Prereq1;Prereq2;Prereq3
            stringstream ss(line);
            string id, name, creditsStr, prereqStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, creditsStr, '|');
            getline(ss, prereqStr);

            int credits = stoi(creditsStr);
            Courses course(id, name, credits);

            // Parse prerequisites
            if (!prereqStr.empty())
            {
                stringstream prereqStream(prereqStr);
                string prereqId;
                while (getline(prereqStream, prereqId, ';'))
                {
                    if (!prereqId.empty())
                        course.addPrerequisite(prereqId);
                }
            }

            courses[id] = course;
        }
        else if (currentSection == "FACULTY")
        {
            // Format: ID|Name|Department|Course1;Course2;Course3
            stringstream ss(line);
            string id, name, dept, coursesStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, dept, '|');
            getline(ss, coursesStr);

            Faculty faculty(id, name, dept);

            // Parse assigned courses
            if (!coursesStr.empty())
            {
                stringstream courseStream(coursesStr);
                string courseId;
                while (getline(courseStream, courseId, ';'))
                {
                    if (!courseId.empty())
                        faculty.assignCourse(courseId);
                }
            }

            faculties[id] = faculty;
        }
        else if (currentSection == "ROOMS")
        {
            // Format: ID|Type|Capacity
            stringstream ss(line);
            string id, type, capacityStr;

            getline(ss, id, '|');
            getline(ss, type, '|');
            getline(ss, capacityStr);

            int capacity = stoi(capacityStr);
            Rooms room(id, type, capacity);

            rooms[id] = room;
        }
        else if (currentSection == "TIMESLOTS")
        {
            // Format: ID|Day|StartTime|EndTime
            stringstream ss(line);
            string id, day, startTime, endTime;

            getline(ss, id, '|');
            getline(ss, day, '|');
            getline(ss, startTime, '|');
            getline(ss, endTime);

            TimeSlots timeSlot(id, day, startTime, endTime);
            timeSlots[id] = timeSlot;
        }
        else if (currentSection == "ENROLLMENTS")
        {
            // Format: StudentID|CourseID|TimeSlotID|SemesterID
            stringstream ss(line);
            string studentId, courseId, timeSlotId, semesterId;

            getline(ss, studentId, '|');
            getline(ss, courseId, '|');
            getline(ss, timeSlotId, '|');
            getline(ss, semesterId);

            Enrollment enrollment(studentId, courseId, timeSlotId, semesterId);
            enrollments.push_back(enrollment);
        }
        else if (currentSection == "DEPARTMENTS")
        {
            // Format: ID|Name|Student1;Student2;Student3
            stringstream ss(line);
            string id, name, studentIdsStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, studentIdsStr);

            Department department(id, name);

            // Parse student IDs
            if (!studentIdsStr.empty())
            {
                stringstream studentStream(studentIdsStr);
                string studentId;
                while (getline(studentStream, studentId, ';'))
                {
                    if (!studentId.empty())
                        department.addStudent(studentId);
                }
            }

            departments[id] = department;
        }
        else if (currentSection == "SEMESTERS")
        {
            // Format: ID|Name|StartDate|EndDate
            stringstream ss(line);
            string id, name, startDate, endDate;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, startDate, '|');
            getline(ss, endDate);

            Semester semester(id, name, startDate, endDate);
            semesters[id] = semester;
        }
    }

    file.close();

    cout << " Loaded data from " << filename << endl;
    cout << "  Students: " << students.size() << endl;
    cout << "  Courses: " << courses.size() << endl;
    cout << "  Faculty: " << faculties.size() << endl;
    cout << "  Rooms: " << rooms.size() << endl;
    cout << "  Time Slots: " << timeSlots.size() << endl;
    cout << "  Enrollments: " << enrollments.size() << endl;
    cout << "  Departments: " << departments.size() << endl;
    cout << "  Semesters: " << semesters.size() << endl;

    buildPrerequisiteGraph();
    return true;
}

bool DataBase::saveToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << " Error: Cannot create file " << filename << endl;
        return false;
    }

    // Save Students
    file << "[STUDENTS]\n";
    for (const auto& pair : students)
    {
        const Student& s = pair.second;
        file << s.getId() << "|"
            << s.getName() << "|"
            << s.getDepartment() << "|"
            << s.getYear() << "|";

        const vector<string>& completed = s.getCompletedCourses();
        for (size_t i = 0; i < completed.size(); i++)
        {
            file << completed[i];
            if (i < completed.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    // Save Courses
    file << "\n[COURSES]\n";
    for (const auto& pair : courses)
    {
        const Courses& c = pair.second;
        file << c.getId() << "|"
            << c.getName() << "|"
            << c.getCredits() << "|";

        const vector<string>& prereqs = c.getPrerequisites();
        for (size_t i = 0; i < prereqs.size(); i++)
        {
            file << prereqs[i];
            if (i < prereqs.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    // Save Faculty
    file << "\n[FACULTY]\n";
    for (const auto& pair : faculties)
    {
        const Faculty& f = pair.second;
        file << f.getId() << "|"
            << f.getName() << "|"
            << f.getDepartment() << "|";

        const vector<string>& courses = f.getAssignedCourses();
        for (size_t i = 0; i < courses.size(); i++)
        {
            file << courses[i];
            if (i < courses.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    // Save Rooms
    file << "\n[ROOMS]\n";
    for (const auto& pair : rooms)
    {
        const Rooms& r = pair.second;
        file << r.getId() << "|"
            << r.getType() << "|"
            << r.getCapacity() << "\n";
    }

    // Save Time Slots
    file << "\n[TIMESLOTS]\n";
    for (const auto& pair : timeSlots)
    {
        const TimeSlots& t = pair.second;
        file << t.getId() << "|"
            << t.getDay() << "|"
            << t.getStartTime() << "|"
            << t.getEndTime() << "\n";
    }

    // Save Enrollments
    file << "\n[ENROLLMENTS]\n";
    for (const Enrollment& e : enrollments)
    {
        file << e.getStudentId() << "|"
            << e.getCourseId() << "|"
            << e.getTimeSlotId() << "|"
            << e.getSemesterId() << "\n";
    }

    // Save Departments
    file << "\n[DEPARTMENTS]\n";
    for (const auto& pair : departments)
    {
        const Department& d = pair.second;
        file << d.getId() << "|"
            << d.getName() << "|";

        const vector<string>& students = d.getStudents();
        for (size_t i = 0; i < students.size(); i++)
        {
            file << students[i];
            if (i < students.size() - 1)
                file << ";";
        }
        file << "\n";
    }

    // Save Semesters
    file << "\n[SEMESTERS]\n";
    for (const auto& pair : semesters)
    {
        const Semester& s = pair.second;
        file << s.getId() << "|"
            << s.getName() << "|"
            << s.getStartDate() << "|"
            << s.getEndDate() << "\n";
    }

    file.close();

    cout << "✓ Saved all data to " << filename << endl;
    cout << "  Students: " << students.size() << endl;
    cout << "  Courses: " << courses.size() << endl;
    cout << "  Faculty: " << faculties.size() << endl;
    cout << "  Rooms: " << rooms.size() << endl;
    cout << "  Time Slots: " << timeSlots.size() << endl;
    cout << "  Enrollments: " << enrollments.size() << endl;
    cout << "  Departments: " << departments.size() << endl;
    cout << "  Semesters: " << semesters.size() << endl;

    return true;
}