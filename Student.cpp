#include "Student.h"
#include <iostream>
using namespace std;

// ---------------- BASE STUDENT ----------------
Student::Student(string id, string n, string e, double g)
    : AcademicEntity(id, n, e) {
    GPA = g;
}

double Student::getGPA() {
    return GPA;
}

Student::~Student() {}


// ---------------- REGULAR STUDENT ----------------
RegularStudent::RegularStudent(string id, string n, string e, double g)
    : Student(id, n, e, g) {
}

double RegularStudent::calculateGPA() {
    return GPA;
}

void RegularStudent::viewTranscript() {
    cout << "Regular Transcript | GPA: " << GPA << endl;
}

void RegularStudent::displayProfile() {
    cout << "[Regular Student] " << name << " | ID: " << ID
        << " | GPA: " << GPA << endl;
}


// ---------------- SCHOLARSHIP STUDENT ----------------
ScholarshipStudent::ScholarshipStudent(string id, string n, string e, double g)
    : Student(id, n, e, g) {
    minGPA = 3.0;
    status = "Active";
}

double ScholarshipStudent::calculateGPA() {
    if (GPA < minGPA)
        status = "Probation";
    else
        status = "Active";

    return GPA;
}

void ScholarshipStudent::viewTranscript() {
    cout << "Scholarship GPA: " << GPA << " | Status: " << status << endl;
}

void ScholarshipStudent::displayProfile() {
    cout << "[Scholarship Student] " << name
        << " | GPA: " << GPA
        << " | Status: " << status << endl;
}


// ---------------- EXCHANGE STUDENT ----------------
ExchangeStudent::ExchangeStudent(string id, string n, string e)
    : Student(id, n, e, 0.0) {
    result = "Pending";
}

double ExchangeStudent::calculateGPA() {
    return 0;
}

void ExchangeStudent::setResult(string r) {
    result = r;
}

void ExchangeStudent::viewTranscript() {
    cout << "Exchange Result: " << result << endl;
}

void ExchangeStudent::displayProfile() {
    cout << "[Exchange Student] " << name
        << " | Result: " << result << endl;
}
