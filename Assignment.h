#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Assessment.h"

class Assignment : public Assessment {

public:
    Assignment(double raw = 0, double max = 0);

    double getWeightedScore() override;
    string getType() override;
};

#endif