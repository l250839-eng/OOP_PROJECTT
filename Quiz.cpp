#include "Quiz.h"

Quiz::Quiz(double raw, double max) : Assessment(raw, max) {}

double Quiz::getWeightedScore() {

    if (maxScore == 0) return 0;

    return (rawScore / maxScore) * 100;
}

string Quiz::getType() {
    return "Quiz";
}