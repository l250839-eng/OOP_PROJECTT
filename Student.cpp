#include "Student.h"
#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;

// =====================================================
// BASE STUDENT
// =====================================================

Student::Student()
{
    GPA = 0;
    enrolledCount = 0;
}

Student::Student(string id,
    string n,
    string e,
    float g)
    : AcademicEntity(id, n, "")
{
    string generatedEmail = n;

    for (int i = 0; i < generatedEmail.length(); i++)
    {
        generatedEmail[i] = tolower(generatedEmail[i]);

        if (generatedEmail[i] == ' ')
        {
            generatedEmail[i] = '.';
        }
    }

    email = generatedEmail + "@gmail.com";

    GPA = g;
    enrolledCount = 0;
}
void Student::enrollCourse(Course* c)
{
    if (enrolledCount < 10)
    {
        enrolledCourses[enrolledCount++] = c;
    }
    else
    {
        cout << "\nMaximum course limit reached!\n";
    }
}

float Student::getGPA()
{
    return GPA;
}

// =====================================================
// REGULAR STUDENT
// =====================================================

RegularStudent::RegularStudent()
{
}

RegularStudent::RegularStudent(string id,
    string n,
    string e,
    float g)
    : Student(id, n, e, g)
{
}

float Student::convertPercentageToGPA(float percentage)
{
    if (percentage >= 85)
        return 4.0f;

    else if (percentage >= 80)
        return 3.7f;

    else if (percentage >= 75)
        return 3.3f;

    else if (percentage >= 70)
        return 3.0f;

    else if (percentage >= 65)
        return 2.7f;

    else if (percentage >= 60)
        return 2.3f;

    else if (percentage >= 55)
        return 2.0f;

    else if (percentage >= 50)
        return 1.0f;

    return 0.0f;
}

void Student::viewTranscript()
{
    cout << "\n===== TRANSCRIPT =====\n";

    cout << "Student ID : "
        << ID << endl;

    cout << "Name       : "
        << name << endl;

    cout << "GPA        : "
        << GPA << endl;
}

void RegularStudent::calculateGPA()
{
    ifstream fin("assessments.txt");

    if (!fin)
    {
        cout << "\nassessments.txt Missing!\n";
        return;
    }

    float totalPercentage = 0;

    int courseCount = 0;

    string sid;
    string cid;
    string type;

    float raw;
    float max;

    string checkedCourses[50];

    int checkedCount = 0;

    while (fin >> sid >> cid >> type >> raw >> max)
    {
        if (sid == ID)
        {
            bool alreadyAdded = false;

            for (int i = 0; i < checkedCount; i++)
            {
                if (checkedCourses[i] == cid)
                {
                    alreadyAdded = true;
                    break;
                }
            }

            if (!alreadyAdded)
            {
                checkedCourses[checkedCount++] = cid;

                float exam = 0;
                float assignment = 0;
                float quiz = 0;

                fin.clear();
                fin.seekg(0);

                string s2;
                string c2;
                string t2;

                float r2;
                float m2;

                while (fin >> s2 >> c2 >> t2 >> r2 >> m2)
                {
                    if (s2 == ID && c2 == cid)
                    {
                        float pct = (r2 / m2) * 100.0f;

                        if (t2 == "Exam")
                        {
                            exam = pct;
                        }

                        else if (t2 == "Assignment")
                        {
                            assignment = pct;
                        }

                        else if (t2 == "Quiz")
                        {
                            quiz = pct;
                        }
                    }
                }

                float finalPercentage =
                    (exam * 0.5f)
                    +
                    (assignment * 0.3f)
                    +
                    (quiz * 0.2f);

                totalPercentage += finalPercentage;

                courseCount++;

                cout << "\n================================";
                cout << "\nCourse ID     : " << cid;
                cout << "\nExam %        : " << exam;
                cout << "\nAssignment %  : " << assignment;
                cout << "\nQuiz %        : " << quiz;
                cout << "\nFinal %       : " << finalPercentage;
                cout << "\n================================\n";
            }
        }
    }

    if (courseCount > 0)
    {
        float averagePercentage =
            totalPercentage / courseCount;

        GPA =
            convertPercentageToGPA(
                averagePercentage
            );
    }

    else
    {
        GPA = 0;
    }

    fin.close();

    cout << "\n================================";
    cout << "\nFINAL SEMESTER GPA = " << GPA;
    cout << "\n================================\n";
}

void RegularStudent::displayProfile()
{
    cout << "\n[Regular Student]\n";
    cout << "ID    : " << ID << "\n";
    cout << "Name  : " << name << "\n";
    cout << "Email : " << email << "\n";
    cout << "GPA   : " << GPA << "\n";
}

string RegularStudent::getType()
{
    return "Regular";
}

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================

ScholarshipStudent::ScholarshipStudent()
{
    minGPA = 2.0f;
    status = "Active";
}

ScholarshipStudent::ScholarshipStudent(
    string id,
    string n,
    string e,
    float g,
    float min)
    : Student(id, n, e, g)
{
    minGPA = min;
    status = "Active";

    checkProbation();
}

void ScholarshipStudent::calculateGPA()
{
    ifstream fin("assessments.txt");

    if (!fin)
    {
        cout << "\nAssessment File Missing!\n";
        return;
    }

    float totalQualityPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < enrolledCount; i++)
    {
        Course* c = enrolledCourses[i];

        float exam = 0;
        float assignment = 0;
        float quiz = 0;

        string sid;
        string cid;
        string type;

        float raw;
        float max;

        fin.clear();
        fin.seekg(0);

        while (fin >> sid >> cid >> type >> raw >> max)
        {
            if (sid == ID && cid == c->getCourseID())
            {
                float pct = (max > 0)
                    ? (raw / max) * 100.0f
                    : 0.0f;

                if (type == "Exam")
                    exam = pct;

                else if (type == "Assignment")
                    assignment = pct;

                else if (type == "Quiz")
                    quiz = pct;
            }
        }

        float finalPct =
            c->calculateFinalPercentage(
                exam,
                assignment,
                quiz
            );

        float courseGPA =
            Student::convertPercentageToGPA(finalPct);

        int credits =
            c->getCreditHours();

        totalQualityPoints +=
            (courseGPA * credits);

        totalCredits += credits;
    }

    if (totalCredits > 0)
    {
        GPA = totalQualityPoints / totalCredits;
    }

    checkProbation();

    cout << "\n================================";
    cout << "\nScholarship Student GPA = " << GPA;
    cout << "\nStatus = " << status;
    cout << "\n================================\n";

    fin.close();
}

void ScholarshipStudent::checkProbation()
{
    status = (GPA < minGPA)
        ? "Probation"
        : "Active";
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

string ScholarshipStudent::getType()
{
    return "Scholarship";
}

float ScholarshipStudent::getMinGPA()
{
    return minGPA;
}

// =====================================================
// EXCHANGE STUDENT
// =====================================================

ExchangeStudent::ExchangeStudent()
{
    GPA = 0;
}

ExchangeStudent::ExchangeStudent(
    string id,
    string n,
    string e)
    : Student(id, n, e, 0)
{
}

void ExchangeStudent::calculateGPA()
{
    cout << "\nExchange Students use PASS/FAIL grading.\n";
    cout << "No numeric GPA is calculated.\n";
}

void ExchangeStudent::viewTranscript()
{
    cout << "\n========== TRANSCRIPT ==========\n";

    cout << "Student Type : Exchange\n";
    cout << "ID           : " << ID << "\n";
    cout << "Name         : " << name << "\n";
    cout << "Grade System : PASS / FAIL\n";

    cout << "\nRegistered Courses:\n";

    for (int i = 0; i < enrolledCount; i++)
    {
        cout << enrolledCourses[i]->getTitle()
            << " -> PASS\n";
    }

    cout << "================================\n";
}

void ExchangeStudent::displayProfile()
{
    cout << "\n[Exchange Student]\n";
    cout << "ID     : " << ID << "\n";
    cout << "Name   : " << name << "\n";
    cout << "Email  : " << email << "\n";
    cout << "Result : PASS / FAIL\n";
}

string ExchangeStudent::getType()
{
    return "Exchange";
}


