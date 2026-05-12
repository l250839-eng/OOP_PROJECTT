#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <fstream>
#include <string>
#include "AcademicEntity.h"
using namespace std;

// =====================================================
// ABSTRACT BASE: Student
// =====================================================
class Student : public AcademicEntity {
protected:
    float  GPA;
    string enrolledSections[10];
    int    enrolledCount;

public:
    Student();
    Student(string id, string n, string e, float g);

    virtual void   calculateGPA() = 0;
    virtual void   viewTranscript();          // base version shows numeric GPA
    void           addEnrolledSection(string sec);
    float          getGPA();
    virtual string getType() = 0;
    void           setGPA(float g);
};

// =====================================================
// REGULAR STUDENT
// =====================================================
class RegularStudent : public Student {
public:
    RegularStudent();
    RegularStudent(string id, string n, string e, float g);
    void   calculateGPA() override;
    void   displayProfile() override;
    string getType() override;
};

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================
class ScholarshipStudent : public Student {
private:
    float  minGPA;
    string status;

public:
    ScholarshipStudent();
    ScholarshipStudent(string id, string n, string e,
        float g, float min);
    void   calculateGPA() override;
    void   checkProbation();
    string getType() override;
    void   displayProfile() override;
    float  getMinGPA();
};

// =====================================================
// EXCHANGE STUDENT
// =====================================================
class ExchangeStudent : public Student {
public:
    ExchangeStudent();
    ExchangeStudent(string id, string n, string e);
    void   calculateGPA() override;
    void   viewTranscript() override;   // FIX: shows Pass/Fail, no numeric GPA
    string getType() override;
    void   displayProfile() override;
};

#endif
