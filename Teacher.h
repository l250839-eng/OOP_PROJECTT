#ifndef TEACHER_H
#define TEACHER_H

#include "AcademicEntity.h"
#include <iostream>
#include <string>
using namespace std;

class Teacher : public AcademicEntity {

private:
    double ratings[100];
    int ratingCount;

    string comments[100];
    int commentCount;

    string assignedCourses[20];
    int courseCount;

public:
    Teacher(string id = "", string n = "", string e = "");

    void addFeedback(double score, string comment);
    double getAverageRating();
    float getAverageFeedback();

    void assignCourse(string cid);

    void displayProfile() override;

    string getID();
    string getName();
    string getEmail();
};

#endif
