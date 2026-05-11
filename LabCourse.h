#ifndef LABCOURSE_H
#define LABCOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class LabCourse : public Course {

public:

    LabCourse(
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