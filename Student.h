#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

#include "AcademicEntity.h"
#include "Course.h"

using namespace std;

// =====================================================
// BASE STUDENT CLASS
// =====================================================

class Student : public AcademicEntity
{
protected:

    float GPA;

    // Maximum 10 enrolled courses
    Course* enrolledCourses[10];

    int enrolledCount;

public:

    Student();

    Student(string id,
        string n,
        string e,
        float g);

    // Course Registration
    void enrollCourse(Course* c);

    // GPA Calculation
    virtual void calculateGPA() = 0;

    // Transcript
    virtual void viewTranscript();

    // Getter
    float getGPA();
    float convertPercentageToGPA(float percentage);
    // Student Type
    virtual string getType() = 0;
};

// =====================================================
// REGULAR STUDENT
// =====================================================

class RegularStudent : public Student
{
public:

    RegularStudent();

    RegularStudent(string id,
        string n,
        string e,
        float g);

    void calculateGPA();

    void displayProfile();

    string getType();

    
};

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================

class ScholarshipStudent : public Student
{
private:

    float minGPA;

    string status;

public:

    ScholarshipStudent();

    ScholarshipStudent(string id,
        string n,
        string e,
        float g,
        float min);

    void calculateGPA();

    void checkProbation();

    void displayProfile();

    string getType();

    float getMinGPA();
};

// =====================================================
// EXCHANGE STUDENT
// =====================================================

class ExchangeStudent : public Student
{
public:

    ExchangeStudent();

    ExchangeStudent(string id,
        string n,
        string e);

    void calculateGPA();

    void viewTranscript();

    void displayProfile();

    string getType();
};

#endif