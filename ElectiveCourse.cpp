#include "ElectiveCourse.h"



ElectiveCourse::ElectiveCourse(
    string cid,
    string t,
    string tid
) : Course(cid, t, tid) {

}

float ElectiveCourse::calculateFinalGrade(
    float exam,
    float assignment,
    float quiz
) {

    return (
        exam * 0.40 +
        assignment * 0.40 +
        quiz * 0.20
        );
}

int ElectiveCourse::getExamDuration() {

    return 2;
}

string ElectiveCourse::getType() {

    return "Elective";
}
