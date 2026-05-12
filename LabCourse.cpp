#include "LabCourse.h"
#include "WeighatgeManager.h"

LabCourse::LabCourse() {}

LabCourse::LabCourse(string cid, string t, string tid)
    : Course(cid, t, tid, 1,
        0.0f,  // Lab has no exam
        WeightageManager::get().getAssignmentWeight("Lab"),
        WeightageManager::get().getQuizWeight("Lab"))
{
}

float LabCourse::calculateFinalPercentage(float /*exam*/, float assignment, float quiz)
{
    return (assignment * assignmentWeight) + (quiz * quizWeight);
}

string LabCourse::getCourseType() { return "Lab"; }

void LabCourse::displayCourse()
{
    Course::displayCourse();
    cout << "\nType       : Lab (No Exam)";
    cout << "\nWeightages : Assign=" << assignmentWeight * 100 << "% "
        << "Quiz=" << quizWeight * 100 << "%\n";
}