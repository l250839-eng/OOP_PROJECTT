#include "Student.h"

// =====================================================
// BASE STUDENT
// =====================================================

Student::Student() {

    GPA = 0;
    enrolledCount = 0;
}

Student::Student(
    string id,
    string n,
    string e,
    float g
) : AcademicEntity(id, n, e) {

    GPA = g;
    enrolledCount = 0;
}

void Student::viewTranscript() {

    cout << "\n========== TRANSCRIPT ==========\n";

    cout << "ID   : " << ID << endl;
    cout << "Name : " << name << endl;
    cout << "GPA  : " << GPA << endl;

    cout << "\nRegistered Sections:\n";

    for (int i = 0; i < enrolledCount; i++) {

        cout << enrolledSections[i] << endl;
    }
}

void Student::addEnrolledSection(string sec) {

    enrolledSections[enrolledCount++] = sec;
}

float Student::getGPA() {

    return GPA;
}

void Student::setGPA(float g) {

    GPA = g;
}

// =====================================================
// HELPER FUNCTION
// =====================================================

float convertPercentageToGPA(float p) {

    if (p >= 85)
        return 4.0;

    else if (p >= 80)
        return 3.7;

    else if (p >= 75)
        return 3.3;

    else if (p >= 70)
        return 3.0;

    else if (p >= 65)
        return 2.7;

    else if (p >= 60)
        return 2.3;

    else if (p >= 55)
        return 2.0;

    else if (p >= 50)
        return 1.0;

    return 0.0;
}
string RegularStudent::getType() {

    return "Regular";
}
string ScholarshipStudent::getType() {

    return "Scholarship";
}
string ExchangeStudent::getType() {

    return "Exchange";
}

// =====================================================
// REGULAR STUDENT
// =====================================================

RegularStudent::RegularStudent() {

}

RegularStudent::RegularStudent(
    string id,
    string n,
    string e,
    float g
) : Student(id, n, e, g) {

}

void RegularStudent::calculateGPA() {

    ifstream fin("assessments.txt");

    ifstream w("weightages.txt");

    if (!fin || !w) {

        cout << "\nRequired Files Missing!\n";
        return;
    }

    float examW;
    float assignmentW;
    float quizW;

    string courseType;

    while (
        w >> courseType
        >> examW
        >> assignmentW
        >> quizW
        ) {

        if (courseType == "Core")
            break;
    }

    string sec;
    string type;

    float raw;
    float max;

    float exam = 0;
    float assignment = 0;
    float quiz = 0;

    while (fin >> sec >> type >> raw >> max) {

        float percentage = (raw / max) * 100;

        if (type == "Exam")
            exam = percentage;

        else if (type == "Assignment")
            assignment = percentage;

        else if (type == "Quiz")
            quiz = percentage;
    }

    float finalPercentage = (
        exam * examW +
        assignment * assignmentW +
        quiz * quizW
        ) / 100.0;

    GPA = convertPercentageToGPA(
        finalPercentage
    );

    cout << "\nFinal Percentage : "
        << finalPercentage;

    cout << "\nUpdated GPA : "
        << GPA
        << endl;

    fin.close();
    w.close();
}

void RegularStudent::displayProfile() {

    cout << "\n[Regular Student]\n";

    cout << "ID    : " << ID << endl;
    cout << "Name  : " << name << endl;
    cout << "Email : " << email << endl;
    cout << "GPA   : " << GPA << endl;
}

// =====================================================
// SCHOLARSHIP STUDENT
// =====================================================

ScholarshipStudent::ScholarshipStudent() {

}

ScholarshipStudent::ScholarshipStudent(
    string id,
    string n,
    string e,
    float g,
    float min
) : Student(id, n, e, g) {

    minGPA = min;
    status = "Active";
}

void ScholarshipStudent::calculateGPA() {

    ifstream fin("assessments.txt");

    ifstream w("weightages.txt");

    if (!fin || !w) {

        cout << "\nRequired Files Missing!\n";
        return;
    }

    float examW;
    float assignmentW;
    float quizW;

    string courseType;

    while (
        w >> courseType
        >> examW
        >> assignmentW
        >> quizW
        ) {

        if (courseType == "Core")
            break;
    }

    string sec;
    string type;

    float raw;
    float max;

    float exam = 0;
    float assignment = 0;
    float quiz = 0;

    while (fin >> sec >> type >> raw >> max) {

        float percentage = (raw / max) * 100;

        if (type == "Exam")
            exam = percentage;

        else if (type == "Assignment")
            assignment = percentage;

        else if (type == "Quiz")
            quiz = percentage;
    }

    float finalPercentage = (
        exam * examW +
        assignment * assignmentW +
        quiz * quizW
        ) / 100.0;

    GPA = convertPercentageToGPA(
        finalPercentage
    );

    checkProbation();

    cout << "\nUpdated GPA : "
        << GPA
        << endl;

    fin.close();
    w.close();
}
void ScholarshipStudent::checkProbation() {

    if (GPA < minGPA) {

        status = "Probation";
    }

    else {

        status = "Active";
    }
}

void ScholarshipStudent::displayProfile() {

    cout << "\n[Scholarship Student]\n";

    cout << "ID      : " << ID << endl;
    cout << "Name    : " << name << endl;
    cout << "Email   : " << email << endl;
    cout << "GPA     : " << GPA << endl;
    cout << "Status  : " << status << endl;
}

// =====================================================
// EXCHANGE STUDENT
// =====================================================

ExchangeStudent::ExchangeStudent() {

    GPA = 0;
}

ExchangeStudent::ExchangeStudent(
    string id,
    string n,
    string e
) : Student(id, n, e, 0) {

}

void ExchangeStudent::calculateGPA() {

    cout << "\nExchange Students Use Pass/Fail System\n";
}

void ExchangeStudent::displayProfile() {

    cout << "\n[Exchange Student]\n";

    cout << "ID    : " << ID << endl;
    cout << "Name  : " << name << endl;
    cout << "Email : " << email << endl;

    cout << "Result : PASS/FAIL\n";
}