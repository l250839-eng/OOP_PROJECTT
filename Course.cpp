#include "Course.h"

// ================= CONSTRUCTOR =================
Course::Course(string id,
    string t,
    string tid,
    string ty) {

    courseID = id;
    title = t;
    teacherID = tid;
    type = ty;

    assessmentCount = 0;
    studentCount = 0;

    for (int i = 0; i < 20; i++) {
        assessments[i] = nullptr;
    }

    for (int i = 0; i < 50; i++) {
        students[i] = nullptr;
    }
}

// ================= ENROLL STUDENT =================
void Course::enrollStudent(Student* s) {

    if (studentCount < 50) {
        students[studentCount] = s;
        studentCount++;
    }
}

// ================= GET STUDENT COUNT =================
int Course::getStudentCount() {
    return studentCount;
}

// ================= ADD ASSESSMENT =================
void Course::addAssessment(Assessment* a) {

    if (assessmentCount < 20) {
        assessments[assessmentCount] = a;
        assessmentCount++;
    }
}

// ================= GETTERS =================
string Course::getCourseID() {
    return courseID;
}

string Course::getTitle() {
    return title;
}

string Course::getTeacherID() {
    return teacherID;
}

string Course::getType() {
    return type;
}

// ================= DESTRUCTOR =================
Course::~Course() {

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i] != nullptr) {
            delete assessments[i];
            assessments[i] = nullptr;
        }
    }

    for (int i = 0; i < studentCount; i++) {
        students[i] = nullptr;
    }
}