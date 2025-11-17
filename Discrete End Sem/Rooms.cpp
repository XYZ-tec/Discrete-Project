#include "Rooms.h"
Rooms::Rooms(string id, string type, int capacity): id(id), type(type), capacity(capacity) {}

string Rooms::getId() const 
{
    return id;
}

string Rooms::getType() const
{
    return type;
}

int Rooms::getCapacity() const 
{
    return capacity;
}

void Rooms::display() const 
{
    cout << "Room ID: " << id << endl;
    cout << "Type: " << type << endl;
    cout << "Capacity: " << capacity << endl;
}