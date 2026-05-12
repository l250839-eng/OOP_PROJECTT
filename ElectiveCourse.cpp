#include "ElectiveCourse.h"
#include "WeighatgeManager.h"

ElectiveCourse::ElectiveCourse() {}

ElectiveCourse::ElectiveCourse(string cid, string t, string tid)
    : Course(cid, t, tid, 3,
        WeightageManager::get().getExamWeight("Elective"),
        WeightageManager::get().getAssignmentWeight("Elective"),
        WeightageManager::get().getQuizWeight("Elective"))
{
}

float ElectiveCourse::calculateFinalPercentage(float exam, float assignment, float quiz)
{
    return (exam * examWeight) + (assignment * assignmentWeight) + (quiz * quizWeight);
}

string ElectiveCourse::getCourseType() { return "Elective"; }

void ElectiveCourse::displayCourse()
{
    Course::displayCourse();
    cout << "\nType       : Elective";
    cout << "\nWeightages : Exam=" << examWeight * 100 << "% "
        << "Assign=" << assignmentWeight * 100 << "% "
        << "Quiz=" << quizWeight * 100 << "%\n";
}



