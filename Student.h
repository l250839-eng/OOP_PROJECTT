#ifndef STUDENT_H
#define STUDENT_H

#include "AcademicEntity.h"

#include <iostream>
#include <string>

using namespace std;

class Student : public AcademicEntity {

protected:

    string type;

    double GPA;

    // TRANSCRIPT
    string completedCourses[20];

    double courseGrades[20];

    int completedCount;

    // ENROLLED
    string enrolledSections[20];

    int enrolledCount;

    // PASS FAIL
    string passFailCourses[20];

    bool passStatus[20];

    int pfCount;

    bool probation;

public:

    Student(string id = "",
        string n = "",
        string e = "",
        string t = "Regular",
        double g = 0);

    virtual ~Student() {}

    // =====================================================
    // GPA
    // =====================================================

    virtual void calculateGPA();

    double getGPA();

    void addCompletedCourse(string course,
        double percentage);

    // =====================================================
    // REGISTRATION
    // =====================================================

    void addEnrolledSection(string sec);

    // =====================================================
    // TRANSCRIPT
    // =====================================================

    virtual void viewTranscript();

    // =====================================================
    // PASS FAIL
    // =====================================================

    void addPassFailCourse(string course,
        bool pass);

    // =====================================================
    // PROBATION
    // =====================================================

    virtual void checkProbation();

    // =====================================================
    // DISPLAY
    // =====================================================

    virtual void displayProfile() = 0;

    // =====================================================
    // GETTERS
    // =====================================================

    string getEmail();

    string getID();

    string getName();

    string getType();
};

// =====================================================
// REGULAR STUDENT
// =====================================================

class RegularStudent : public Student {

public:

    RegularStudent(string id = "",
        string n = "",
        string e = "",
        double g = 0);

    void displayProfile() override;
};

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================

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

// =====================================================
// EXCHANGE STUDENT
// =====================================================

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