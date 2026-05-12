#include "Course.h"
#include <iostream>
using namespace std;

// =====================================================
// CONSTRUCTORS / DESTRUCTOR
// =====================================================
Course::Course() {
    courseID = "";
    title = "";
    teacherID = "";
    assessmentCount = 0;
    for (int i = 0; i < MAX_ASSESSMENTS; i++)
        assessments[i] = nullptr;
}

Course::Course(string cid, string t, string tid) {
    courseID = cid;
    title = t;
    teacherID = tid;
    assessmentCount = 0;
    for (int i = 0; i < MAX_ASSESSMENTS; i++)
        assessments[i] = nullptr;
}

Course::~Course() {
    clearAssessments();
}

// =====================================================
// GETTERS
// =====================================================
string Course::getCourseID() { return courseID; }
string Course::getTitle() { return title; }
string Course::getTeacherID() { return teacherID; }

// =====================================================
// ASSESSMENT ARRAY MANAGEMENT
// =====================================================
void Course::addAssessment(Assessment* a) {
    if (a == nullptr) return;
    if (assessmentCount >= MAX_ASSESSMENTS) {
        cout << "WARNING: Assessment array full for course "
            << courseID << "\n";
        return;
    }
    assessments[assessmentCount++] = a;
}

void Course::clearAssessments() {
    for (int i = 0; i < assessmentCount; i++) {
        delete assessments[i];
        assessments[i] = nullptr;
    }
    assessmentCount = 0;
}

int Course::getAssessmentCount() {
    return assessmentCount;
}

Assessment* Course::getAssessment(int index) {
    if (index < 0 || index >= assessmentCount) return nullptr;
    return assessments[index];
}

// =====================================================
// CALCULATE FINAL GRADE FROM STORED ASSESSMENTS
// Walks the Assessment* array, buckets each type by
// getType(), averages each bucket, then calls the
// virtual calculateFinalGrade() so each course subclass
// applies its own weightages automatically.
// =====================================================
float Course::calculateFinalGradeFromAssessments() {
    float examTotal = 0, examMax = 0;
    float assignTotal = 0, assignMax = 0;
    float quizTotal = 0, quizMax = 0;

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i] == nullptr) continue;
        string type = assessments[i]->getType();
        if (type == "Exam") {
            examTotal += assessments[i]->getRawScore();
            examMax += assessments[i]->getMaxScore();
        }
        else if (type == "Assignment") {
            assignTotal += assessments[i]->getRawScore();
            assignMax += assessments[i]->getMaxScore();
        }
        else if (type == "Quiz") {
            quizTotal += assessments[i]->getRawScore();
            quizMax += assessments[i]->getMaxScore();
        }
    }

    // Convert each bucket to a percentage (0-100); default 0 if no entries
    float examPct = (examMax > 0) ? (examTotal / examMax) * 100.0f : 0.0f;
    float assignPct = (assignMax > 0) ? (assignTotal / assignMax) * 100.0f : 0.0f;
    float quizPct = (quizMax > 0) ? (quizTotal / quizMax) * 100.0f : 0.0f;

    // Delegate to the polymorphic weightage logic
    return calculateFinalGrade(examPct, assignPct, quizPct);
}
