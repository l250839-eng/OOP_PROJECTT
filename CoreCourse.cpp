#include "CoreCourse.h"

CoreCourse::CoreCourse()
{
}

CoreCourse::CoreCourse(string cid,
    string t,
    string tid)
    : Course(cid,
        t,
        tid,
        3,
        0.70f,
        0.20f,
        0.10f)
{
}

float CoreCourse::calculateFinalPercentage(float exam,
    float assignment,
    float quiz)
{
    return (exam * examWeight)
        + (assignment * assignmentWeight)
        + (quiz * quizWeight);
}

string CoreCourse::getCourseType()
{
    return "Core";
}
void CoreCourse::displayCourse()
{
    Course::displayCourse();

    cout << "\nType       : Core\n";
}