#include "ElectiveCourse.h"

ElectiveCourse::ElectiveCourse()
{
}

ElectiveCourse::ElectiveCourse(string cid,
    string t,
    string tid)
    : Course(cid,
        t,
        tid,
        3,
        0.50f,
        0.30f,
        0.20f)
{
}

float ElectiveCourse::calculateFinalPercentage(float exam,
    float assignment,
    float quiz)
{
    return (exam * examWeight)
        + (assignment * assignmentWeight)
        + (quiz * quizWeight);
}

string ElectiveCourse::getCourseType()
{
    return "Elective";
}





