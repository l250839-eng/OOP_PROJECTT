#include "DatabaseManager.h"
#include "CoreCourse.h"
#include "ElectiveCourse.h"
#include "LabCourse.h"
#include "Exam.h"
#include "Quiz.h"
#include "Assignment.h"
#include "StudentAssessment.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// =====================================================
// STUDENTS — SAVE
// =====================================================
void DatabaseManager::saveStudents(Student* students[], int count) {
    ofstream file("students.txt");
    for (int i = 0; i < count; i++) {
        if (students[i] == nullptr) continue;
        string type = students[i]->getType();
        float  gpa = students[i]->getGPA();
        string extra = "-";
        if (type == "Scholarship") {
            ScholarshipStudent* ss = static_cast<ScholarshipStudent*>(students[i]);
            extra = to_string(ss->getMinGPA());
        }
        else if (type == "Exchange") {
            extra = "PASS";
        }
        file << students[i]->getID() << " "
            << students[i]->getName() << " "
            << type << " "
            << gpa << " "
            << extra << "\n";
    }
    file.close();
}

// =====================================================
// STUDENTS — LOAD
// =====================================================
void DatabaseManager::loadStudents(Student* students[], int& count) {
    ifstream file("students.txt");
    string id, name, type, extra;
    double gpa;
    count = 0;
    while (file >> id >> name >> type >> gpa >> extra) {
        string email = name + "@nu.edu.pk";
        if (type == "Regular") {
            students[count] = new RegularStudent(id, name, email, (float)gpa);
        }
        else if (type == "Scholarship") {
            double minGPA = stod(extra);
            students[count] = new ScholarshipStudent(id, name, email,
                (float)gpa, (float)minGPA);
        }
        else if (type == "Exchange") {
            students[count] = new ExchangeStudent(id, name, email);
        }
        count++;
    }
    file.close();
}

// =====================================================
// TEACHERS — SAVE
// =====================================================
void DatabaseManager::saveTeachers(Teacher* teachers[], int count) {
    ofstream file("teachers.txt");
    for (int i = 0; i < count; i++) {
        if (teachers[i] == nullptr) continue;
        file << teachers[i]->getID() << " "
            << teachers[i]->getName() << " "
            << teachers[i]->getAverageRating() << "\n";
    }
    file.close();
}

// =====================================================
// TEACHERS — LOAD
// =====================================================
void DatabaseManager::loadTeachers(Teacher* teachers[], int& count) {
    ifstream file("teachers.txt");
    string id, name;
    double rating;
    count = 0;
    while (file >> id >> name >> rating) {
        string email = name + "@nu.edu.pk";
        Teacher* t = new Teacher(id, name, email);
        t->addFeedback(rating, "Loaded");
        teachers[count++] = t;
    }
    file.close();
}

// =====================================================
// COURSES — SAVE
// =====================================================
void DatabaseManager::saveCourses(Course* courses[], int count) {
    ofstream file("courses.txt");
    for (int i = 0; i < count; i++) {
        if (courses[i] == nullptr) continue;
        file << courses[i]->getCourseID() << " "
            << courses[i]->getTitle() << " "
            << courses[i]->getTeacherID() << " "
            << courses[i]->getType() << "\n";
    }
    file.close();
}

// =====================================================
// COURSES — LOAD
// =====================================================
void DatabaseManager::loadCourses(Course* courses[], int& count) {
    ifstream file("courses.txt");
    string id, title, tid, type;
    count = 0;
    while (file >> id >> title >> tid >> type) {
        if (type == "Core")     courses[count] = new CoreCourse(id, title, tid);
        else if (type == "Elective") courses[count] = new ElectiveCourse(id, title, tid);
        else if (type == "Lab")      courses[count] = new LabCourse(id, title, tid);
        count++;
    }
    file.close();
}

// =====================================================
// SECTIONS — SAVE
// =====================================================
void DatabaseManager::saveSections(Section* sections[], int count) {
    ofstream file("sections.txt");
    for (int i = 0; i < count; i++) {
        if (sections[i] == nullptr) continue;
        file << sections[i]->getSectionID() << " "
            << sections[i]->getCourseID() << " "
            << sections[i]->getTeacherID() << " "
            << sections[i]->getVenue() << " "
            << sections[i]->getTimeSlot() << "\n";
    }
    file.close();
}

// =====================================================
// SECTIONS — LOAD
// =====================================================
void DatabaseManager::loadSections(Section* sections[], int& count) {
    ifstream file("sections.txt");
    string sid, cid, tid, vid, time;
    count = 0;
    while (file >> sid >> cid >> tid >> vid >> time) {
        Section* s = new Section(sid, time, cid);
        s->setTeacherID(tid);
        s->setVenue(vid);
        sections[count++] = s;
    }
    file.close();
}

// =====================================================
// VENUES — SAVE
// =====================================================
void DatabaseManager::saveVenues(Venue venues[], int count) {
    ofstream file("venues.txt");
    for (int i = 0; i < count; i++) {
        file << venues[i].getRoomID() << " "
            << venues[i].getCapacity() << " "
            << venues[i].hasComputers() << "\n";
    }
    file.close();
}

// =====================================================
// VENUES — LOAD
// =====================================================
void DatabaseManager::loadVenues(Venue venues[], int& count) {
    ifstream file("venues.txt");
    string id;
    int    cap;
    bool   comp;
    count = 0;
    while (file >> id >> cap >> comp) {
        venues[count++] = Venue(id, cap, comp);
    }
    file.close();
}

// =====================================================
// ASSESSMENTS — SAVE  (FIX: was completely missing)
// Walks every Course's Assessment* array and writes
// each one to assessments.txt.
// Format: CourseID Type RawScore MaxScore
// =====================================================
void DatabaseManager::saveAssessments(Course* courses[], int courseCount) {
    ofstream file("assessments.txt");
    for (int i = 0; i < courseCount; i++) {
        if (courses[i] == nullptr) continue;
        int n = courses[i]->getAssessmentCount();
        for (int j = 0; j < n; j++) {
            Assessment* a = courses[i]->getAssessment(j);
            if (a == nullptr) continue;
            file << courses[i]->getCourseID() << " "
                << a->getType() << " "
                << a->getRawScore() << " "
                << a->getMaxScore() << "\n";
        }
    }
    file.close();
}

// =====================================================
// ASSESSMENTS — LOAD  (FIX: was completely missing)
// Reads assessments.txt and re-attaches each record
// to the matching Course object as a new Assessment*.
// The old arrays are cleared first to avoid duplicates.
// =====================================================
void DatabaseManager::loadAssessments(Course* courses[], int courseCount) {
    // Clear existing assessments in every course first
    for (int i = 0; i < courseCount; i++) {
        if (courses[i] != nullptr)
            courses[i]->clearAssessments();
    }

    ifstream file("assessments.txt");
    if (!file) return;   // file may not exist yet on first run

    string cid, type;
    double raw, max;
    while (file >> cid >> type >> raw >> max) {
        // Find the matching course
        for (int i = 0; i < courseCount; i++) {
            if (courses[i] == nullptr) continue;
            if (courses[i]->getCourseID() != cid) continue;

            // Build the correct polymorphic Assessment object
            Assessment* a = nullptr;
            if (type == "Exam")       a = new Exam(raw, max);
            else if (type == "Quiz")       a = new Quiz(raw, max);
            else if (type == "Assignment") a = new Assignment(raw, max);

            if (a != nullptr)
                courses[i]->addAssessment(a);
            break;
        }
    }
    file.close();
}

// =====================================================
// LINK SECTIONS TO COURSES
// =====================================================
void DatabaseManager::linkSectionsToCourses(Course* courses[], int courseCount,
    Section* sections[], int sectionCount) {
    for (int i = 0; i < sectionCount; i++) {
        if (sections[i] == nullptr) continue;
        string cid = sections[i]->getCourseID();
        for (int j = 0; j < courseCount; j++) {
            if (courses[j] == nullptr) continue;
            if (courses[j]->getCourseID() == cid) {
                sections[i]->setCourse(courses[j]);
                break;
            }
        }
    }
}


void DatabaseManager::saveStudentAssessment(
    string sid,
    string cid,
    string type,
    float raw,
    float max
) {

    ofstream fout(
        "assessments.txt",
        ios::app
    );

    fout << sid << "|"
        << cid << "|"
        << type << "|"
        << raw << "|"
        << max << endl;

    fout.close();
}
float DatabaseManager::calculateStudentGrade(
    string sid,
    string cid,
    string courseType
) {

    ifstream fin("assessments.txt");

    string studentID;
    string courseID;
    string type;

    float raw;
    float max;

    float examPercent = 0;
    float assignmentPercent = 0;
    float quizPercent = 0;

    while (
        getline(fin, studentID, '|')
        ) {

        getline(fin, courseID, '|');
        getline(fin, type, '|');

        fin >> raw;
        fin.ignore();

        fin >> max;
        fin.ignore();

        if (
            studentID == sid
            &&
            courseID == cid
            ) {

            float percent =
                (raw / max) * 100;

            if (type == "Exam")
                examPercent = percent;

            else if (type == "Assignment")
                assignmentPercent = percent;

            else if (type == "Quiz")
                quizPercent = percent;
        }
    }

    fin.close();

    // ================= WEIGHTAGES =================

    float finalGrade = 0;

    if (courseType == "Core") {

        finalGrade =
            (examPercent * 0.70)
            +
            (assignmentPercent * 0.20)
            +
            (quizPercent * 0.10);
    }

    else if (courseType == "Elective") {

        finalGrade =
            (examPercent * 0.40)
            +
            (assignmentPercent * 0.40)
            +
            (quizPercent * 0.20);
    }

    else if (courseType == "Lab") {

        finalGrade =
            (assignmentPercent * 0.50)
            +
            (quizPercent * 0.50);
    }

    return finalGrade;
}