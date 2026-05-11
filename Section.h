

#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>

#include "Course.h"
#include "Student.h"

using namespace std;

class Section {

private:

    string sectionID;
    string timeSlot;

    string courseID;
    string teacherID;

    string venueID;

    Course* course;

    Student* students[50];

    int studentCount;

    int capacity;

public:

    

    Section(string id = "",
        string time = "",
        string cid = "");

    

    void setCourse(Course* c);

    void setVenue(string v);

    void setTeacherID(string id);

    

    string getSectionID();

    string getTimeSlot();

    string getCourseID();

    string getTeacherID();

    string getVenue();

    Course* getCourse();

   
    string getCourseType();

    

    bool addStudent(Student* s);

    bool isFull();

    int getStudentCount();

    

    void displaySection();
};

#endif