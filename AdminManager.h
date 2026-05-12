#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include <iostream>
#include "Student.h"

using namespace std;

class AdminManager {

private:

    Student* students[100];
    int count;

public:

   
    AdminManager();

   
    bool addStudent(Student* s);

  
    Student* searchStudent(string id);

   
    void displayAllStudents();

    
    void clear();

    
    int getCount();
};

#endif