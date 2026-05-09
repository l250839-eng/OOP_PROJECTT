#ifndef STUDENT_H
#define STUDENT_H

#include "AcademicEntity.h"

// ---------------- BASE STUDENT ----------------
class Student : public AcademicEntity {
protected:
    double GPA;

public:
    Student(string id = "", string n = "", string e = "", double g = 0.0);

    virtual double calculateGPA() = 0;
    virtual void viewTranscript() = 0;

    double getGPA();
    virtual ~Student();
};

// ---------------- REGULAR ----------------
class RegularStudent : public Student {
public:
    RegularStudent(string id = "", string n = "", string e = "", double g = 0.0);

    double calculateGPA() override;
    void viewTranscript() override;
    void displayProfile() override;
};

// ---------------- SCHOLARSHIP ----------------
class ScholarshipStudent : public Student {
private:
    double minGPA;
    string status;

public:
    ScholarshipStudent(string id = "", string n = "", string e = "", double g = 0.0);

    double calculateGPA() override;
    void viewTranscript() override;
    void displayProfile() override;
};

// ---------------- EXCHANGE ----------------
class ExchangeStudent : public Student {
private:
    string result;

public:
    ExchangeStudent(string id = "", string n = "", string e = "");

    double calculateGPA() override;
    void setResult(string r);
    void viewTranscript() override;
    void displayProfile() override;
};

#endif

