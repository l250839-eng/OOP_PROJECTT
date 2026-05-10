#include "Student.h"


// BASE STUDENT


Student::Student(string id, string n, string e, double g)
    : AcademicEntity(id, n, e) {

    GPA = g;

    completedCount = 0;
    pfCount = 0;

    probation = false;
}



void Student::calculateGPA() {

    if (completedCount == 0) {
        GPA = 0;
        return;
    }

    double total = 0;

    for (int i = 0; i < completedCount; i++) {

        double p = courseGrades[i];

        if (p >= 85) total += 4.0;
        else if (p >= 80) total += 3.7;
        else if (p >= 75) total += 3.3;
        else if (p >= 70) total += 3.0;
        else if (p >= 65) total += 2.7;
        else if (p >= 60) total += 2.0;
        else if (p >= 50) total += 1.0;
        else total += 0;
    }

    GPA = total / completedCount;
}


double Student::getGPA() {
    return GPA;
}


void Student::addCompletedCourse(string course, double percentage) {

    if (completedCount >= 20) {
        cout << "ERROR: Course limit reached!\n";
        return;
    }

    completedCourses[completedCount] = course;
    courseGrades[completedCount] = percentage;

    completedCount++;

    calculateGPA();
}


void Student::viewTranscript() {

    cout << "\n===== TRANSCRIPT =====\n";

    for (int i = 0; i < completedCount; i++) {

        cout << completedCourses[i]
            << " : "
            << courseGrades[i]
            << "%\n";
    }

    cout << "GPA: " << GPA << endl;
}



void Student::addPassFailCourse(string course, bool pass) {

    if (pfCount >= 20) {
        cout << "ERROR: Pass/Fail limit reached!\n";
        return;
    }

    passFailCourses[pfCount] = course;
    passStatus[pfCount] = pass;

    pfCount++;
}


void Student::checkProbation() {
    
}


string Student::getID() {
    return ID;
}

string Student::getName() {
    return name;
}


RegularStudent::RegularStudent(string id, string n, string e, double g)
    : Student(id, n, e, g) {
}

void RegularStudent::displayProfile() {

    cout << "\n===== REGULAR STUDENT =====\n";
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "GPA: " << GPA << endl;
}


// SCHOLARSHIP STUDENT


ScholarshipStudent::ScholarshipStudent(string id, string n, string e, double g, double min)
    : Student(id, n, e, g) {

    minGPA = min;
}

void ScholarshipStudent::checkProbation() {

    probation = (GPA < minGPA);
}

void ScholarshipStudent::displayProfile() {

    cout << "\n===== SCHOLARSHIP STUDENT =====\n";
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "GPA: " << GPA << endl;

    cout << "STATUS: " << (probation ? "PROBATION" : "SAFE") << endl;
}


// EXCHANGE STUDENT


ExchangeStudent::ExchangeStudent(string id, string n, string e)
    : Student(id, n, e, 0) {
}

void ExchangeStudent::calculateGPA() {
    GPA = 0;
}

void ExchangeStudent::viewTranscript() {

    cout << "\n===== PASS / FAIL TRANSCRIPT =====\n";

    for (int i = 0; i < pfCount; i++) {

        cout << passFailCourses[i] << " : "
            << (passStatus[i] ? "PASS" : "FAIL") << endl;
    }
}

void ExchangeStudent::displayProfile() {

    cout << "\n===== EXCHANGE STUDENT =====\n";
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
}