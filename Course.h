
#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

#include "Assessment.h"
#include "Student.h"

using namespace std;

class Course {

protected:

    string courseID;
    string title;
    string teacherID;
    string type;

    Assessment* assessments[20];
    int assessmentCount;

    Student* students[50];
    int studentCount;

public:

    // ================= CONSTRUCTOR =================
    Course(string id = "",
        string t = "",
        string tid = "",
        string ty = "");

    // ================= STUDENTS =================
    void enrollStudent(Student* s);
    int getStudentCount();

    // ================= ASSESSMENTS =================
    void addAssessment(Assessment* a);

    // ================= GETTERS =================
    string getCourseID();
    string getTitle();
    string getTeacherID();
    string getType();

    // ================= CORE =================
    virtual double calculateFinalGrade() = 0;
    virtual int getExamDuration() = 0;

    // ================= DESTRUCTOR =================
    virtual ~Course();
};

#endif