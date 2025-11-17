#pragma once
#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include "Student.h"
#include "Courses.h"
#include "Faculty.h"
#include "Rooms.h"
#include "TimeSlots.h"
#include "Enrollment.h"
#include "Transcript.h"
#include "Department.h"
#include "Semester.h"
using namespace std;
class DataBase 
{
private:
    map<string, Student> students; 
    map<string, Courses> courses;
    map<string, Faculty> faculties;
    map<string, Rooms> rooms;
    map<string, TimeSlots> timeSlots;
    vector<Enrollment> enrollments;
    map<string, Transcript> transcripts;
    map<string, Department> departments;
    map<string, Semester> semesters;
    map<string, vector<string>> prerequisiteGraph;

public:
    void addStudent(const Student& s);
    void addCourse(const Courses& c);
    void addFaculty(const Faculty& f);
    void addRoom(const Rooms& r);
    void addTimeSlot(const TimeSlots& t);
    void addEnrollment(const Enrollment& e);
    void addTranscript(const Transcript& t);
    void addDepartment(const Department& d);
    void addSemester(const Semester& s);

    Student* getStudent(string id);
    Courses* getCourse(string id);
    Faculty* getFaculty(string id);
    Rooms* getRoom(string id);
    TimeSlots* getTimeSlot(string id);
    Department* getDepartment(string id);
    Semester* getSemester(string id);

    void displayAllStudents() const;
    void displayAllCourses() const;
    void displayAllFaculty() const;

    void buildPrerequisiteGraph();
    bool canEnroll(string studentId, string courseId);
    vector<string> getAvailableCourses(string studentId);
    bool hasCircularDependency();
    vector<string> getValidCourseSequence();
    set<string> getAllPrerequisites(string courseId);
    bool hasTimeConflict(string studentId, string courseId, string timeSlotId);
    bool hasFacultyConflict(string facultyId, string timeSlotId);
    vector<string> getEnrolledStudents(string courseId);
    vector<string> getStudentCourses(string studentId);
};

#endif