#ifndef TEACHER_H
#define TEACHER_H

#include "AcademicEntity.h"

class Teacher : public AcademicEntity {
private:
    double averageFeedback;

public:
    Teacher(string id = "", string n = "", string e = "", double f = 0.0);

    void addFeedback(double rating);
    double getFeedback();
    void displayProfile() override;
};

#endif