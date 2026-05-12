#ifndef CORECOURSE_H
#define CORECOURSE_H

#include "Course.h"

class CoreCourse : public Course
{
public:
    CoreCourse();

    CoreCourse(string cid,
        string t,
        string tid);

    float calculateFinalPercentage(float exam,
        float assignment,
        float quiz);

    string getCourseType();
    void displayCourse();
};

#endif
