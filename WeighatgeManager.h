#ifndef WEIGHTAGEMANAGER_H
#define WEIGHTAGEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class WeightageManager {
private:
    string courseTypes[10];
    float  examW[10];
    float  assignW[10];
    float  quizW[10];
    int    count;

    static WeightageManager* instance;  // singleton
    WeightageManager();

public:
    // Singleton accessor — loads file once
    static WeightageManager& get();

    void loadFromFile(string filename = "weightages.txt");

    float getExamWeight(string courseType);
    float getAssignmentWeight(string courseType);
    float getQuizWeight(string courseType);
};

#endif
