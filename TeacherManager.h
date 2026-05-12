#ifndef TEACHERMANAGER_H
#define TEACHERMANAGER_H

#include <iostream>
#include "Teacher.h"

using namespace std;

class TeacherManager {

private:

    Teacher* teachers[100];
    int count;

public:

    TeacherManager();

    bool addTeacher(Teacher* t);

    Teacher* searchTeacher(string id);

    void displayAllTeachers();

    void clear();

    int getCount();
};

#endif