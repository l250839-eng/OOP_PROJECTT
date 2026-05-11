#include "Student.h"

// =====================================================
// STUDENT BASE CLASS
// =====================================================

Student::Student(string id,
    string n,
    string e,
    string t,
    double g) {

    ID = id;
    name = n;
    email = e;

    type = t;
    GPA = g;

    completedCount = 0;
    pfCount = 0;

    probation = false;
    enrolledCount = 0;
}

// =====================================================
// GETTERS
// =====================================================

string Student::getID() {
    return ID;
}

string Student::getName() {
    return name;
}

string Student::getEmail() {
    return email;
}

string Student::getType() {
    return type;
}

double Student::getGPA() {
    return GPA;
}

// =====================================================
// GPA CALCULATION
// =====================================================

void Student::calculateGPA() {

    double sum = 0;

    for (int i = 0; i < completedCount; i++) {
        sum += courseGrades[i];
    }

    if (completedCount != 0) {
        GPA = sum / completedCount;
    }
}

// =====================================================
// COURSE MANAGEMENT
// =====================================================

void Student::addCompletedCourse(string course,
    double percentage) {

    completedCourses[completedCount] = course;
    courseGrades[completedCount] = percentage;
    completedCount++;
}

// =====================================================
// TRANSCRIPT
// =====================================================

void Student::viewTranscript() {

    cout << "\n===== TRANSCRIPT =====\n";

    cout << "Name: "
        << name
        << endl;

    cout << "GPA: "
        << GPA
        << endl;

    cout << "\nCompleted Courses:\n";

    for (int i = 0; i < completedCount; i++) {

        cout << completedCourses[i]
            << " : "
            << courseGrades[i]
            << endl;
    }

    cout << "\nRegistered Sections:\n";

    for (int i = 0; i < enrolledCount; i++) {

        cout << enrolledSections[i]
            << endl;
    }

    cout << endl;
}

// =====================================================
// PASS / FAIL
// =====================================================

void Student::addPassFailCourse(string course,
    bool pass) {

    passFailCourses[pfCount] = course;
    passStatus[pfCount] = pass;
    pfCount++;
}

// =====================================================
// PROBATION
// =====================================================

void Student::checkProbation() {

    if (GPA < 2.0) {
        probation = true;
    }
}

// =====================================================
// DISPLAY BASE
// =====================================================

void Student::displayProfile() {

    cout << "\n===== STUDENT PROFILE =====\n";
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Type: " << type << endl;
    cout << "GPA: " << GPA << endl;
}

// =====================================================
// REGULAR STUDENT
// =====================================================

RegularStudent::RegularStudent(string id,
    string n,
    string e,
    double g)
    : Student(id, n, e, "Regular", g) {
}

void RegularStudent::displayProfile() {

    Student::displayProfile();
}

// =====================================================
// SCHOLARSHIP STUDENT (FIXED)
// =====================================================

ScholarshipStudent::ScholarshipStudent(string id,
    string n,
    string e,
    double g,
    double min)
    : Student(id, n, e, "Scholarship", g) {

    minGPA = min;
}

void ScholarshipStudent::checkProbation() {

    if (GPA < minGPA) {
        probation = true;
    }
}

void ScholarshipStudent::displayProfile() {

    Student::displayProfile();

    cout << "Min GPA Requirement: " << minGPA << endl;
}

// =====================================================
// EXCHANGE STUDENT
// =====================================================

ExchangeStudent::ExchangeStudent(string id,
    string n,
    string e)
    : Student(id, n, e, "Exchange", 0) {
}

void ExchangeStudent::calculateGPA() {
    GPA = 0; // pass/fail system
}

void ExchangeStudent::viewTranscript() {

    cout << "\n===== EXCHANGE TRANSCRIPT =====\n";
    cout << "Name: " << name << endl;
    cout << "Status: Pass/Fail System\n";
}

void ExchangeStudent::displayProfile() {

    Student::displayProfile();
    cout << "System: Pass/Fail\n";
}
void Student::addEnrolledSection(string sec) {

    enrolledSections[enrolledCount] = sec;

    enrolledCount++;
}