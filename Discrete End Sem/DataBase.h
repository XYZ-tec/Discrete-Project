#pragma once
#ifndef UNIVERSITYDATABASE_H
#define UNIVERSITYDATABASE_H
#include<iostream>
#include <map>
#include <vector>
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
class UniversityDataBase 
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
    Student* getStudent(std::string id);
    Courses* getCourse(std::string id);
    void displayAllStudents() const;
    void displayAllCourses() const;
    // Will add more methods as needed with the further needs
};

#endif