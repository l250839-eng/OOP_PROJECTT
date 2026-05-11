#include "Assessment.h"


Assessment::Assessment(double r, double m) {
    rawScore = r;
    maxScore = m;
}


double Assessment::getRawScore() {
    return rawScore;
}


double Assessment::getMaxScore() {
    return maxScore;
}