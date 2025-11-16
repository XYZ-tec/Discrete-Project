#pragma once
#ifndef TIMESLOTS_H
#define TIMESLOTS_H
#include<iostream>
#include <string>
using namespace std;
class TimeSlots
{
private:
    string id;
    string day;
    string startTime;
    string endTime;

public:
	TimeSlots() {}
    TimeSlots(string id, string day, string start, string end);
    string getId() const;
    string getDay() const;
    string getStartTime() const;
    string getEndTime() const;
    bool overlaps(const TimeSlots& other) const;  // For conflict detection
    void display() const;
};

#endif