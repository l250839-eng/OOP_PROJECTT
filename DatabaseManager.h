
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Section.h"
#include "Venue.h"

using namespace std;

class DatabaseManager {

public:

   

    void saveStudents(Student* students[],
        int count);

    void loadStudents(Student* students[],
        int& count);

   

    void saveTeachers(Teacher* teachers[],
        int count);

    void loadTeachers(Teacher* teachers[],
        int& count);

   

    void saveCourses(Course* courses[],
        int count);

    void loadCourses(Course* courses[],
        int& count);

   

    void saveSections(Section* sections[],
        int count);

    void loadSections(Section* sections[],
        int& count);

    

    void saveVenues(Venue venues[],
        int count);

    void loadVenues(Venue venues[],
        int& count);

   

    void linkSectionsToCourses(
        Course* courses[],
        int courseCount,
        Section* sections[],
        int sectionCount
    );
};

#endif