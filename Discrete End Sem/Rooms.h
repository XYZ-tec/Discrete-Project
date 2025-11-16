#pragma once
#ifndef ROOMS_H
#define ROOMS_H
#include<iostream>
#include <string>
using namespace std;
class Rooms 
{
private:
    string id;
    string type;  // e.g Lecture or Lab etc
    int capacity;

public:
    Rooms() {}
    Rooms(string id, string type, int capacity);
    string getId() const;
    string getType() const;
    int getCapacity() const;
    void display() const;
};

#endif