#ifndef STUDENT_H
#define STUDENT_H

#include "AcademicEntity.h"
#include <iostream>
#include <string>

using namespace std;

class Student : public AcademicEntity {

protected:

    double GPA;

    string completedCourses[20];
    double courseGrades[20];
    int completedCount;

    string passFailCourses[20];
    bool passStatus[20];
    int pfCount;

    bool probation;

public:

    Student(string id = "",
        string n = "",
        string e = "",
        double g = 0);

    virtual ~Student() {}

    // GPA SYSTEM
    virtual void calculateGPA();
    double getGPA();

    void addCompletedCourse(string course, double percentage);

    virtual void viewTranscript();

    // PASS / FAIL
    void addPassFailCourse(string course, bool pass);

    // PROBATION
    virtual void checkProbation();

   
    virtual void displayProfile() = 0;

    // GETTERS
    string getID();
    string getName();
};



// REGULAR STUDENT


class RegularStudent : public Student {

public:

    RegularStudent(string id = "",
        string n = "",
        string e = "",
        double g = 0);

    void displayProfile() override;
};


// SCHOLARSHIP STUDENT

class ScholarshipStudent : public Student {

private:
    double minGPA;

public:

    ScholarshipStudent(string id = "",
        string n = "",
        string e = "",
        double g = 0,
        double min = 3.0);

    void checkProbation() override;
    void displayProfile() override;
};




// EXCHANGE STUDENT


class ExchangeStudent : public Student {

public:

    ExchangeStudent(string id = "",
        string n = "",
        string e = "");

    void calculateGPA() override;
    void viewTranscript() override;
    void displayProfile() override;
};

#endif