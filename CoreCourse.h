#ifndef CORECOURSE_H
#define CORECOURSE_H

#include "Course.h"
#include "WeighatgeManager.h"

class CoreCourse : public Course {

public:

    CoreCourse(string id = "",
        string t = "",
        string tid = "");

    double calculateFinalGrade() override;

    int getExamDuration() override;
};

#endif