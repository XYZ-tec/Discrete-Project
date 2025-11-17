#include "TimeSlots.h"

TimeSlots::TimeSlots(string id, string day, string start, string end): id(id), day(day), startTime(start), endTime(end) {}

string TimeSlots::getId() const 
{
    return id;
}

string TimeSlots::getDay() const
{
    return day;
}

string TimeSlots::getStartTime() const 
{
    return startTime;
}

string TimeSlots::getEndTime() const 
{
    return endTime;
}

bool TimeSlots::overlaps(const TimeSlots& other) const 
{
    if (day != other.day) 
    {
        return false;
    }

	// Check time overlaping simple string comparison works for HH:MM format  (hour:minute)
    // Overlap occurs if : (start1 < end2) AND (start2 < end1)
    return (startTime < other.endTime) && (other.startTime < endTime);
}

void TimeSlots::display() const 
{
    cout << "Time Slot ID: " << id << endl;
    cout << "Day: " << day << endl;
    cout << "Time: " << startTime << " - " << endTime << endl;
}