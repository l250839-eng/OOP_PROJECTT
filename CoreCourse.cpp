#include "CoreCourse.h"


CoreCourse::CoreCourse(string id,
    string t,
    string tid)
    : Course(id, t, tid, "Core") {
}



double CoreCourse::calculateFinalGrade() {

    WeightageManager wm;

    wm.loadFromFile("weightages.txt");

    double examTotal = 0;
    double quizTotal = 0;
    double assignmentTotal = 0;

    int examCount = 0;
    int quizCount = 0;
    int assignmentCount = 0;

   

    for (int i = 0; i < assessmentCount; i++) {

        if (assessments[i] == nullptr) {
            continue;
        }

        double score = assessments[i]->getWeightedScore();

        string t = assessments[i]->getType();

       

        if (t == "Exam") {

            examTotal += score;

            examCount++;
        }

       

        else if (t == "Quiz") {

            quizTotal += score;

            quizCount++;
        }

       
        else if (t == "Assignment") {

            assignmentTotal += score;

            assignmentCount++;
        }
    }

   
    double examAverage = 0;
    double quizAverage = 0;
    double assignmentAverage = 0;

    if (examCount > 0) {

        examAverage = examTotal / examCount;
    }

    if (quizCount > 0) {

        quizAverage = quizTotal / quizCount;
    }

    if (assignmentCount > 0) {

        assignmentAverage =
            assignmentTotal / assignmentCount;
    }


    double finalGrade = 0;

    finalGrade +=
        examAverage *
        wm.getExamWeight(type) / 100.0;

    finalGrade +=
        quizAverage *
        wm.getQuizWeight(type) / 100.0;

    finalGrade +=
        assignmentAverage *
        wm.getAssignmentWeight(type) / 100.0;

    return finalGrade;
}



int CoreCourse::getExamDuration() {

    return 180;
}