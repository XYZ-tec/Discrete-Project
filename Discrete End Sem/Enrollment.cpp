#include "Enrollment.h"

Enrollment::Enrollment(string sId, string cId, string tId, string semId): studentId(sId), courseId(cId), timeSlotId(tId), semesterId(semId) {}

string Enrollment::getStudentId() const 
{
    return studentId;
}

string Enrollment::getCourseId() const 
{
    return courseId;
}

string Enrollment::getTimeSlotId() const 
{
    return timeSlotId;
}

string Enrollment::getSemesterId() const
{
    return semesterId;
}

void Enrollment::display() const
{
    cout << "Enrollment Details:" << endl;
    cout << "Student ID: " << studentId << endl;
    cout << "Course ID: " << courseId << endl;
    cout << "Time Slot ID: " << timeSlotId << endl;
    cout << "Semester ID: " << semesterId << endl;
}