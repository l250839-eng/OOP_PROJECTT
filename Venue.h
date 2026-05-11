#ifndef VENUE_H
#define VENUE_H

#include <iostream>
using namespace std;

class Venue {

private:

    string roomID;
    int capacity;
    bool computers;  

public:

    Venue(string id = "", int cap = 0, bool comp = false);

    string getRoomID();
    int getCapacity();

    bool hasComputers();   

    void setRoomID(string id);
    void setCapacity(int cap);
    void setComputers(bool c);
};

#endif