#include "Student.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// =====================================================
// BASE STUDENT
// =====================================================
Student::Student()
{
    GPA = 0;
    enrolledCount = 0;
    for (int i = 0; i < 10; i++) enrolledCourses[i] = nullptr;
}

Student::Student(string id, string n, string e, float g)
    : AcademicEntity(id, n, "")
{
    string generatedEmail = n;
    for (int i = 0; i < (int)generatedEmail.length(); i++) {
        generatedEmail[i] = tolower(generatedEmail[i]);
        if (generatedEmail[i] == ' ') generatedEmail[i] = '.';
    }
    email = generatedEmail + "@gmail.com";
    GPA = g;
    enrolledCount = 0;
    for (int i = 0; i < 10; i++) enrolledCourses[i] = nullptr;
}

void Student::enrollCourse(Course* c)
{
    if (enrolledCount < 10)
        enrolledCourses[enrolledCount++] = c;
    else
        cout << "\nMaximum course limit (10) reached!\n";
}

float Student::getGPA() { return GPA; }

float Student::convertPercentageToGPA(float p)
{
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

void Student::viewTranscript()
{
    cout << "\n===== TRANSCRIPT =====\n";
    cout << "Student ID : " << ID << "\n";
    cout << "Name       : " << name << "\n";
    cout << "GPA        : " << GPA << "\n";
}

// =====================================================
// HELPER: read assessments for one student+course
// from assessments.txt and return exam/assign/quiz %
// =====================================================
static void readScoresFromFile(const string& sid, const string& cid,
    float& exam, float& assign, float& quiz)
{
    exam = assign = quiz = 0;
    ifstream fin("assessments.txt");
    if (!fin) return;

    string s, c, t;
    float  raw, max;
    while (fin >> s >> c >> t >> raw >> max) {
        if (s != sid || c != cid) continue;
        float pct = (max > 0) ? (raw / max) * 100.0f : 0.0f;
        if (t == "Exam")       exam = pct;
        else if (t == "Assignment") assign = pct;
        else if (t == "Quiz")       quiz = pct;
    }
    fin.close();
}

// =====================================================
// REGULAR STUDENT — uses course->calculateFinalPercentage
// =====================================================
RegularStudent::RegularStudent() {}

RegularStudent::RegularStudent(string id, string n, string e, float g)
    : Student(id, n, e, g) {
}

void RegularStudent::calculateGPA()
{
    if (enrolledCount == 0) {
        cout << "\nNo enrolled courses to calculate GPA.\n";
        return;
    }

    float totalPoints = 0;
    int   totalCredits = 0;

    cout << "\n========== GPA CALCULATION ==========\n";

    for (int i = 0; i < enrolledCount; i++) {
        Course* c = enrolledCourses[i];
        float exam, assign, quiz;
        readScoresFromFile(ID, c->getCourseID(), exam, assign, quiz);

        float finalPct = c->calculateFinalPercentage(exam, assign, quiz);
        float courseGPA = convertPercentageToGPA(finalPct);
        int   credits = c->getCreditHours();

        cout << "\nCourse     : " << c->getTitle()
            << "  [" << c->getCourseType() << "]";
        cout << "\nExam %     : " << exam;
        cout << "\nAssign %   : " << assign;
        cout << "\nQuiz %     : " << quiz;
        cout << "\nFinal %    : " << finalPct;
        cout << "\nCourse GPA : " << courseGPA << "\n";

        totalPoints += courseGPA * credits;
        totalCredits += credits;
    }

    GPA = (totalCredits > 0) ? totalPoints / totalCredits : 0;

    cout << "\n=====================================";
    cout << "\nFINAL CGPA = " << GPA;
    cout << "\n=====================================\n";
}

void RegularStudent::displayProfile()
{
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
ScholarshipStudent::ScholarshipStudent()
{
    minGPA = 2.0f;
    status = "Active";
}

ScholarshipStudent::ScholarshipStudent(string id, string n, string e, float g, float min)
    : Student(id, n, e, g)
{
    minGPA = min;
    status = "Active";
    checkProbation();
}

void ScholarshipStudent::calculateGPA()
{
    if (enrolledCount == 0) {
        cout << "\nNo enrolled courses to calculate GPA.\n";
        return;
    }

    float totalPoints = 0;
    int   totalCredits = 0;

    cout << "\n========== SCHOLARSHIP GPA ==========\n";

    for (int i = 0; i < enrolledCount; i++) {
        Course* c = enrolledCourses[i];
        float exam, assign, quiz;
        readScoresFromFile(ID, c->getCourseID(), exam, assign, quiz);

        float finalPct = c->calculateFinalPercentage(exam, assign, quiz);
        float courseGPA = convertPercentageToGPA(finalPct);
        int   credits = c->getCreditHours();

        cout << "\nCourse     : " << c->getTitle()
            << "  [" << c->getCourseType() << "]";
        cout << "\nFinal %    : " << finalPct;
        cout << "\nCourse GPA : " << courseGPA << "\n";

        totalPoints += courseGPA * credits;
        totalCredits += credits;
    }

    GPA = (totalCredits > 0) ? totalPoints / totalCredits : 0;
    checkProbation();

    cout << "\n=====================================";
    cout << "\nScholarship GPA = " << GPA;
    cout << "\nStatus          = " << status;
    if (status == "Probation")
        cout << "  *** WARNING: Below minimum " << minGPA << " ***";
    cout << "\n=====================================\n";
}

void ScholarshipStudent::checkProbation()
{
    status = (GPA < minGPA) ? "Probation" : "Active";
}

void ScholarshipStudent::displayProfile()
{
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
// EXCHANGE STUDENT — FIX: real PASS/FAIL check (>=50%)
// =====================================================
ExchangeStudent::ExchangeStudent() { GPA = 0; }
ExchangeStudent::ExchangeStudent(string id, string n, string e)
    : Student(id, n, e, 0) {
}

void ExchangeStudent::calculateGPA()
{
    cout << "\nExchange Students use PASS/FAIL grading. No numeric GPA.\n";
}

void ExchangeStudent::viewTranscript()
{
    cout << "\n========== EXCHANGE TRANSCRIPT ==========\n";
    cout << "Student Type : Exchange\n";
    cout << "ID           : " << ID << "\n";
    cout << "Name         : " << name << "\n";
    cout << "Grade System : PASS / FAIL  (pass threshold: 50%)\n\n";

    for (int i = 0; i < enrolledCount; i++) {
        Course* c = enrolledCourses[i];
        float exam, assign, quiz;
        readScoresFromFile(ID, c->getCourseID(), exam, assign, quiz);

        // FIX: actually compute the percentage and decide
        float finalPct = c->calculateFinalPercentage(exam, assign, quiz);
        string result = (finalPct >= 50.0f) ? "PASS" : "FAIL";

        cout << c->getTitle() << "  ->  " << result
            << "  (" << finalPct << "%)\n";
    }
    cout << "=========================================\n";
}

void ExchangeStudent::displayProfile()
{
    cout << "\n[Exchange Student]\n";
    cout << "ID     : " << ID << "\n";
    cout << "Name   : " << name << "\n";
    cout << "Email  : " << email << "\n";
    cout << "Result : PASS / FAIL\n";
}

string ExchangeStudent::getType() { return "Exchange"; }

