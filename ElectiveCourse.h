#ifndef ELECTIVECOURSE_H
#define ELECTIVECOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class ElectiveCourse : public Course {

public:

    ElectiveCourse(string id = "",
        string t = "",
        string tid = "");

    double calculateFinalGrade() override;

    int getExamDuration() override;
};

#endif