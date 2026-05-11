#ifndef LABCOURSE_H
#define LABCOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class LabCourse : public Course {

public:

    LabCourse(string id = "",
        string t = "",
        string tid = "");

    double calculateFinalGrade() override;

    int getExamDuration() override;
};

#endif