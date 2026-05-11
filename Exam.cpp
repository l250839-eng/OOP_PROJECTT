#include "Exam.h"

Exam::Exam(double raw, double max) : Assessment(raw, max) {}

double Exam::getWeightedScore() {

    if (maxScore == 0) return 0;

    return (rawScore / maxScore) * 100;
}

string Exam::getType() {
    return "Exam";
}