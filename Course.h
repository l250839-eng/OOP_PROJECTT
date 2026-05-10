#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

#include "Assessment.h"
#include "Student.h"
#include "WeighatgeManager.h"

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

    

    Course(string id = "",
        string t = "",
        string tid = "",
        string ty = "");

   

    void enrollStudent(Student* s);

    int getStudentCount();

    

    void addAssessment(Assessment* a);

   

    string getCourseID();

    string getTitle();

    string getTeacherID();

    string getType();

    

    virtual double calculateFinalGrade() = 0;

    virtual int getExamDuration() = 0;

   

    virtual ~Course();
};

#endif