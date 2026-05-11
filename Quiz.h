#ifndef QUIZ_H
#define QUIZ_H

#include "Assessment.h"

class Quiz : public Assessment {

public:
    Quiz(double raw = 0, double max = 0);

    double getWeightedScore() override;
    string getType() override;
};

#endif