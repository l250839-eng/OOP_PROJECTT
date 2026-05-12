#ifndef ELECTIVECOURSE_H
#define ELECTIVECOURSE_H

#include "Course.h"

class ElectiveCourse : public Course
{
public:
    ElectiveCourse();

    ElectiveCourse(string cid,
        string t,
        string tid);

    float calculateFinalPercentage(float exam,
        float assignment,
        float quiz);

    string getCourseType();
    
};

#endif
