#include "LabCourse.h"

// =====================================================
// CONSTRUCTOR
// =====================================================

LabCourse::LabCourse(string id,
    string t,
    string tid)
    : Course(id, t, tid, "Lab") {
}

// =====================================================
// FINAL GRADE
// =====================================================

double LabCourse::calculateFinalGrade() {

    WeightageManager wm;

    wm.loadFromFile("weightages.txt");

    double quizTotal = 0;
    double assignmentTotal = 0;

    int quizCount = 0;
    int assignmentCount = 0;

    // =================================================
    // LOOP THROUGH ASSESSMENTS
    // =================================================

    for (int i = 0; i < assessmentCount; i++) {

        if (assessments[i] == nullptr) {
            continue;
        }

        double score = assessments[i]->getWeightedScore();

        string t = assessments[i]->getType();

        // ---------------- QUIZ ----------------

        if (t == "Quiz") {

            quizTotal += score;

            quizCount++;
        }

        // ---------------- ASSIGNMENT ----------------

        else if (t == "Assignment") {

            assignmentTotal += score;

            assignmentCount++;
        }
    }

    // =================================================
    // AVERAGES
    // =================================================

    double quizAverage = 0;
    double assignmentAverage = 0;

    if (quizCount > 0) {

        quizAverage = quizTotal / quizCount;
    }

    if (assignmentCount > 0) {

        assignmentAverage =
            assignmentTotal / assignmentCount;
    }

    // =================================================
    // APPLY WEIGHTAGES
    // =================================================

    double finalGrade = 0;

    finalGrade +=
        quizAverage *
        wm.getQuizWeight(type) / 100.0;

    finalGrade +=
        assignmentAverage *
        wm.getAssignmentWeight(type) / 100.0;

    return finalGrade;
}

// =====================================================
// EXAM DURATION
// =====================================================

int LabCourse::getExamDuration() {

    return 0;
}