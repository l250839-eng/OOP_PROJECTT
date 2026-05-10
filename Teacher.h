
#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <string>
using namespace std;

class Teacher {

private:

    string ID;
    string name;
    string email;

    int ratings[50];
    string comments[50];
    int count;

public:

    Teacher(string id = "",
        string n = "",
        string e = "");

    void addFeedback(int rating, string comment);

    double getAverageRating();

    void displayProfile();

    void displayFeedback();  

    string getID();
    string getName();
};

#endif