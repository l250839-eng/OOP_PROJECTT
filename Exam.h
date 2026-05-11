#ifndef EXAM_H
#define EXAM_H

#include "Assessment.h"

class Exam : public Assessment {

public:
    Exam(double raw = 0, double max = 0);

    double getWeightedScore() override;
    string getType() override;
};

#endif