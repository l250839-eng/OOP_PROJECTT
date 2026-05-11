#include "CoreCourse.h"


CoreCourse::CoreCourse(
    string cid,
    string t,
    string tid
) : Course(cid, t, tid) {

}

float CoreCourse::calculateFinalGrade(
    float exam,
    float assignment,
    float quiz
) {

    return (
        exam * 0.70 +
        assignment * 0.20 +
        quiz * 0.10
        );
}

int CoreCourse::getExamDuration() {

    return 3;
}

string CoreCourse::getType() {

    return "Core";
}
