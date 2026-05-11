#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <iostream>
#include <string>
using namespace std;

class Assessment {

protected:
    double rawScore;
    double maxScore;

public:
    Assessment(double r = 0, double m = 0);

    virtual double getWeightedScore() = 0;
    virtual string getType() = 0;

    double getRawScore();
    double getMaxScore();

    virtual ~Assessment() {}
};

#endif