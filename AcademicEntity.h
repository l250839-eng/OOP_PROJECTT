#ifndef ACADEMIC_ENTITY_H
#define ACADEMIC_ENTITY_H

#include <iostream>
using namespace std;

class AcademicEntity {
protected:
    string ID;
    string name;
    string email;

public:
    AcademicEntity(string id = "", string n = "", string e = "");
    virtual void displayProfile() = 0;
    virtual ~AcademicEntity();
};

#endif