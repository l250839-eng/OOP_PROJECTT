#ifndef LABCOURSE_H
#define LABCOURSE_H

#include "Course.h"

class LabCourse : public Course
{
public:
    LabCourse();

    LabCourse(string cid,
        string t,
        string tid);

    float calculateFinalPercentage(float exam,
        float assignment,
        float quiz);

    string getCourseType();
    void displayCourse();
};




#endif