#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <string>

#include "AcademicEntity.h"

using namespace std;

class Student : public AcademicEntity {

protected:

    float GPA;

    string enrolledSections[10];
    int enrolledCount;

public:

    Student();

    Student(
        string id,
        string n,
        string e,
        float g
    );

    virtual void calculateGPA() = 0;

    virtual void viewTranscript();

    void addEnrolledSection(string sec);

    float getGPA();

    virtual string getType() = 0;
    void setGPA(float g);
};

// =====================================================
// REGULAR STUDENT
// =====================================================

class RegularStudent : public Student {

public:

    RegularStudent();

    RegularStudent(
        string id,
        string n,
        string e,
        float g
    );

    void calculateGPA();

    void displayProfile();
    string getType();
};

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================

class ScholarshipStudent : public Student {

private:

    float minGPA;
    string status;
    
public:

    ScholarshipStudent();

    ScholarshipStudent(
        string id,
        string n,
        string e,
        float g,
        float min
    );

    void calculateGPA();

    void checkProbation();
    string getType();
    void displayProfile();
};

// =====================================================
// EXCHANGE STUDENT
// =====================================================

class ExchangeStudent : public Student {

public:

    ExchangeStudent();

    ExchangeStudent(
        string id,
        string n,
        string e
    );

    void calculateGPA();
    string getType();
    void displayProfile();
};

#endif