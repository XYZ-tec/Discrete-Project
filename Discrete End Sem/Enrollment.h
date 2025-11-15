#pragma once
#ifndef ENROLLMENT_H
#define ENROLLMENT_H
#include<iostream>
#include <string>
#include "Student.h"
#include "Courses.h"
#include "TimeSlots.h"
using namespace std;
class Enrollment
{
private:
    string studentId;
    string courseId;
    string timeSlotId;
    string semesterId;

public:
    Enrollment(string sId, string cId, string tId, string semId);
    string getStudentId() const;
    string getCourseId() const;
    string getTimeSlotId() const;
    string getSemesterId() const;
    void display() const;
};

#endif