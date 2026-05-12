#ifndef REGISTRATIONMANAGER_H
#define REGISTRATIONMANAGER_H

#include <iostream>
#include "Section.h"
#include "Student.h"

using namespace std;

class RegistrationManager {

public:

    
    bool registerStudent(Student* student, Section* section);

    
    bool hasConflict(Section* s1, Section* s2);
};

#endif