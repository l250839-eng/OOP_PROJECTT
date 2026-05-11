#ifndef TEACHER_H
#define TEACHER_H

#include "AcademicEntity.h"

#include <iostream>
#include <string>

using namespace std;

class Teacher : public AcademicEntity {

private:

    // SIMPLE RATING SYSTEM
    double rating;

    // COMMENTS
    string comments[20];

    int commentCount;

    // COURSES
    string assignedCourses[20];

    int courseCount;

public:

    // =====================================================
    // CONSTRUCTOR
    // =====================================================

    Teacher(string id = "",
        string n = "",
        string e = "");

    // =====================================================
    // FEEDBACK
    // =====================================================

    void addFeedback(double score,
        string comment);

    double getAverageRating();

    // =====================================================
    // COURSES
    // =====================================================

    void assignCourse(string cid);

    // =====================================================
    // DISPLAY
    // =====================================================

    void displayProfile() override;

    // =====================================================
    // GETTERS
    // =====================================================

    string getID();

    string getName();

    string getEmail();
};

#endif
