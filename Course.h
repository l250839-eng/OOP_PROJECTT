#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

using namespace std;

class Course {

protected:

    string courseID;
    string title;
    string teacherID;

public:

    Course();

    Course(
        string cid,
        string t,
        string tid
    );

    virtual float calculateFinalGrade(
        float exam,
        float assignment,
        float quiz
    ) = 0;

    virtual int getExamDuration() = 0;

    virtual string getType() = 0;

    string getCourseID();

    string getTeacherID();
    string getTitle();
};


#endif