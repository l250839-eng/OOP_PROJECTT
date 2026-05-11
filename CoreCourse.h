#ifndef CORECOURSE_H
#define CORECOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class CoreCourse : public Course {

public:

    CoreCourse(
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