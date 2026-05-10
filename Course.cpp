#include "Course.h"



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
}



void Course::enrollStudent(Student* s) {

    

    for (int i = 0; i < studentCount; i++) {

        if (students[i]->getID() == s->getID()) {

            cout << "Student already enrolled!\n";

            return;
        }
    }

   

    if (studentCount >= 50) {

        cout << "Course capacity full!\n";

        return;
    }

   

    students[studentCount] = s;

    studentCount++;

    cout << "Student enrolled successfully!\n";
}



int Course::getStudentCount() {

    return studentCount;
}



void Course::addAssessment(Assessment* a) {

    

    if (assessmentCount >= 20) {

        cout << "Assessment limit reached!\n";

        return;
    }

   

    assessments[assessmentCount] = a;

    assessmentCount++;

    cout << "Assessment added successfully!\n";
}



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



Course::~Course() {

    for (int i = 0; i < assessmentCount; i++) {

        delete assessments[i];
    }
}