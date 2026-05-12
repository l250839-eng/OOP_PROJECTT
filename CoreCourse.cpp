#include "CoreCourse.h"
#include "WeighatgeManager.h"

CoreCourse::CoreCourse() {}

CoreCourse::CoreCourse(string cid, string t, string tid)
    : Course(cid, t, tid, 3,
        WeightageManager::get().getExamWeight("Core"),
        WeightageManager::get().getAssignmentWeight("Core"),
        WeightageManager::get().getQuizWeight("Core"))
{
}

float CoreCourse::calculateFinalPercentage(float exam, float assignment, float quiz)
{
    return (exam * examWeight) + (assignment * assignmentWeight) + (quiz * quizWeight);
}

string CoreCourse::getCourseType() { return "Core"; }

void CoreCourse::displayCourse()
{
    Course::displayCourse();
    cout << "\nType       : Core";
    cout << "\nWeightages : Exam=" << examWeight * 100 << "% "
        << "Assign=" << assignmentWeight * 100 << "% "
        << "Quiz=" << quizWeight * 100 << "%\n";
}
