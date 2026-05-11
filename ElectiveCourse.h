#ifndef ELECTIVECOURSE_H
#define ELECTIVECOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class ElectiveCourse : public Course {

public:

    ElectiveCourse(
        string cid,
        string t,
        string tid
    );

    float calculateFinalGrade(
        float exam,
        float assignment,
        float quiz
    );

    int getExamDuration();

    string getType();
};

#endif