#ifndef TEACHER_H
#define TEACHER_H

#include "AcademicEntity.h"

#include <iostream>
#include <string>

using namespace std;

class Teacher : public AcademicEntity {

private:

    
    double rating;



    float averageFeedback;
    string comments[20];

    int commentCount;

        string assignedCourses[20];

    int courseCount;

public:


    Teacher(string id = "",
        string n = "",
        string e = "");

  
    void addFeedback(double score,
        string comment);

    double getAverageRating();

    

    void assignCourse(string cid);

   

    void displayProfile() override;
    float getAverageFeedback();
    
    string getID();

    string getName();

    string getEmail();
};

#endif
