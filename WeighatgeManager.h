#ifndef WEIGHTAGEMANAGER_H
#define WEIGHTAGEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class WeightageManager {

private:
    string type[10];
    int exam[10];
    int assignment[10];
    int quiz[10];
    int count;

public:

    WeightageManager();

    void loadFromFile(string filename);

    int getExamWeight(string courseType);
    int getAssignmentWeight(string courseType);
    int getQuizWeight(string courseType);
};

#endif