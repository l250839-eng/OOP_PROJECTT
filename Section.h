

#ifndef SECTION_H
#define SECTION_H
#include <iostream>
#include <string>
#include "Course.h"
#include "Student.h"
using namespace std;

class Section {
private:
    string   sectionID;
    string   timeSlot;
    string   courseID;
    string   teacherID;
    string   venueID;
    Course* course;
    Student* students[50];
    int      studentCount;
    int      capacity;

public:
    Section(string id = "",
        string time = "",
        string cid = "");

    // Setters
    void setCourse(Course* c);
    void setVenue(string v);
    void setTeacherID(string id);
    void setCapacity(int cap);      // so Scheduler can push venue capacity in

    // Getters
    string  getSectionID();
    string  getTimeSlot();
    string  getCourseID();
    string  getTeacherID();
    string  getVenue();
    Course* getCourse();
    string  getCourseType();

    // Student management
    bool     addStudent(Student* s);
    bool     isFull();
    int      getStudentCount();
    Student* getStudentAt(int index);   // needed by RegistrationManager conflict check

    void displaySection();
};

#endif
