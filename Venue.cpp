#include "Venue.h"

Venue::Venue(string id, int cap, bool comp) {

    roomID = id;
    capacity = cap;
    computers = comp;
}

string Venue::getRoomID() {
    return roomID;
}

int Venue::getCapacity() {
    return capacity;
}

bool Venue::hasComputers() {
    return computers;
}

void Venue::setRoomID(string id) {
    roomID = id;
}

void Venue::setCapacity(int cap) {
    capacity = cap;
}

void Venue::setComputers(bool c) {
    computers = c;
}