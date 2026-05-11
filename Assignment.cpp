#include "Assignment.h"

Assignment::Assignment(double raw, double max) : Assessment(raw, max) {}

double Assignment::getWeightedScore() {

    if (maxScore == 0) return 0;

    return (rawScore / maxScore) * 100;
}

string Assignment::getType() {
    return "Assignment";
}