#include "Student.h"
#include <iostream>
#include <fstream>
using namespace std;

// =====================================================
// HELPER: percentage -> GPA
// =====================================================
static float convertPercentageToGPA(float p) {
    if (p >= 85) return 4.0f;
    if (p >= 80) return 3.7f;
    if (p >= 75) return 3.3f;
    if (p >= 70) return 3.0f;
    if (p >= 65) return 2.7f;
    if (p >= 60) return 2.3f;
    if (p >= 55) return 2.0f;
    if (p >= 50) return 1.0f;
    return 0.0f;
}

// =====================================================
// BASE STUDENT
// =====================================================
Student::Student() {
    GPA = 0;
    enrolledCount = 0;
}

Student::Student(string id, string n, string e, float g)
    : AcademicEntity(id, n, e) {
    GPA = g;
    enrolledCount = 0;
}

void Student::viewTranscript() {
    cout << "\n========== TRANSCRIPT ==========\n";
    cout << "ID   : " << ID << "\n";
    cout << "Name : " << name << "\n";
    cout << "GPA  : " << GPA << "\n";
    cout << "\nRegistered Sections:\n";
    for (int i = 0; i < enrolledCount; i++)
        cout << "  " << enrolledSections[i] << "\n";
    cout << "================================\n";
}

void Student::addEnrolledSection(string sec) {
    if (enrolledCount < 10)
        enrolledSections[enrolledCount++] = sec;
}

float Student::getGPA() { return GPA; }
void  Student::setGPA(float g) { GPA = g; }

// =====================================================
// REGULAR STUDENT
// =====================================================
RegularStudent::RegularStudent() {}

RegularStudent::RegularStudent(string id, string n, string e, float g)
    : Student(id, n, e, g) {
}

void RegularStudent::calculateGPA() {
    ifstream fin("assessments.txt");
    ifstream w("weightages.txt");
    if (!fin || !w) {
        cout << "\nRequired Files Missing!\n";
        return;
    }
    float examW = 0.70f, assignmentW = 0.20f, quizW = 0.10f;
    string courseType;
    while (w >> courseType >> examW >> assignmentW >> quizW)
        if (courseType == "Core") break;

    string sec, type;
    float raw, max;
    float exam = 0, assignment = 0, quiz = 0;
    while (fin >> sec >> type >> raw >> max) {
        float pct = (max > 0) ? (raw / max) * 100.0f : 0.0f;
        if (type == "Exam")       exam = pct;
        else if (type == "Assignment") assignment = pct;
        else if (type == "Quiz")       quiz = pct;
    }
    float finalPct = (exam * examW + assignment * assignmentW + quiz * quizW) / 100.0f;
    GPA = convertPercentageToGPA(finalPct);
    cout << "\nFinal Percentage : " << finalPct
        << "\nUpdated GPA      : " << GPA << "\n";
    fin.close(); w.close();
}

void RegularStudent::displayProfile() {
    cout << "\n[Regular Student]\n";
    cout << "ID    : " << ID << "\n";
    cout << "Name  : " << name << "\n";
    cout << "Email : " << email << "\n";
    cout << "GPA   : " << GPA << "\n";
}

string RegularStudent::getType() { return "Regular"; }

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================
ScholarshipStudent::ScholarshipStudent() {
    minGPA = 2.0f;
    status = "Active";
}

ScholarshipStudent::ScholarshipStudent(string id, string n, string e,
    float g, float min)
    : Student(id, n, e, g) {
    minGPA = min;
    status = "Active";
    checkProbation();
}

void ScholarshipStudent::calculateGPA() {
    ifstream fin("assessments.txt");
    ifstream w("weightages.txt");
    if (!fin || !w) {
        cout << "\nRequired Files Missing!\n";
        return;
    }
    float examW = 0.70f, assignmentW = 0.20f, quizW = 0.10f;
    string courseType;
    while (w >> courseType >> examW >> assignmentW >> quizW)
        if (courseType == "Core") break;

    string sec, type;
    float raw, max;
    float exam = 0, assignment = 0, quiz = 0;
    while (fin >> sec >> type >> raw >> max) {
        float pct = (max > 0) ? (raw / max) * 100.0f : 0.0f;
        if (type == "Exam")       exam = pct;
        else if (type == "Assignment") assignment = pct;
        else if (type == "Quiz")       quiz = pct;
    }
    float finalPct = (exam * examW + assignment * assignmentW + quiz * quizW) / 100.0f;
    GPA = convertPercentageToGPA(finalPct);
    checkProbation();
    cout << "\nUpdated GPA : " << GPA << "\n";
    fin.close(); w.close();
}

void ScholarshipStudent::checkProbation() {
    status = (GPA < minGPA) ? "Probation" : "Active";
}

void ScholarshipStudent::displayProfile() {
    cout << "\n[Scholarship Student]\n";
    cout << "ID      : " << ID << "\n";
    cout << "Name    : " << name << "\n";
    cout << "Email   : " << email << "\n";
    cout << "GPA     : " << GPA << "\n";
    cout << "Min GPA : " << minGPA << "\n";
    cout << "Status  : " << status << "\n";
}

string ScholarshipStudent::getType() { return "Scholarship"; }
float  ScholarshipStudent::getMinGPA() { return minGPA; }

// =====================================================
// EXCHANGE STUDENT
// =====================================================
ExchangeStudent::ExchangeStudent() { GPA = 0; }

ExchangeStudent::ExchangeStudent(string id, string n, string e)
    : Student(id, n, e, 0) {
}

void ExchangeStudent::calculateGPA() {
    // Exchange students have no numeric GPA — Pass/Fail only
    cout << "\nExchange Students use the Pass/Fail system. No GPA calculated.\n";
}

// FIX: Override viewTranscript to show Pass/Fail instead of a numeric GPA
void ExchangeStudent::viewTranscript() {
    cout << "\n========== TRANSCRIPT (Exchange Student) ==========\n";
    cout << "ID   : " << ID << "\n";
    cout << "Name : " << name << "\n";
    cout << "Grade System : PASS / FAIL  (no numeric GPA)\n";
    cout << "\nRegistered Sections:\n";
    for (int i = 0; i < enrolledCount; i++) {
        cout << "  " << enrolledSections[i] << "  ->  PASS\n";
    }
    cout << "===================================================\n";
}

void ExchangeStudent::displayProfile() {
    cout << "\n[Exchange Student]\n";
    cout << "ID     : " << ID << "\n";
    cout << "Name   : " << name << "\n";
    cout << "Email  : " << email << "\n";
    cout << "Result : PASS / FAIL\n";
}

string ExchangeStudent::getType() { return "Exchange"; }
