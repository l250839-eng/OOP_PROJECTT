#include "LabCourse.h"

LabCourse::LabCourse(
    string cid,
    string t,
    string tid
) : Course(cid, t, tid) {

}

float LabCourse::calculateFinalGrade(
    float exam,
    float assignment,
    float quiz
) {

    return (
        assignment * 0.60 +
        quiz * 0.40
        );
}

int LabCourse::getExamDuration() {

    return 0;
}

string LabCourse::getType() {

    return "Lab";
}