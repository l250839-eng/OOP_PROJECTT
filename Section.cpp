#include "Section.h"

// =====================================================
// CONSTRUCTOR
// =====================================================

Section::Section(string id,
    string time,
    string cid) {

    sectionID = id;

    timeSlot = time;

    courseID = cid;

    teacherID = "";

    venueID = "";

    course = nullptr;

    studentCount = 0;

    capacity = 50;
}

// =====================================================
// SETTERS
// =====================================================

void Section::setCourse(Course* c) {

    course = c;
}

void Section::setVenue(string v) {

    venueID = v;
}

void Section::setTeacherID(string id) {

    teacherID = id;
}

// =====================================================
// GETTERS
// =====================================================

string Section::getSectionID() {

    return sectionID;
}

string Section::getTimeSlot() {

    return timeSlot;
}

string Section::getCourseID() {

    return courseID;
}

string Section::getTeacherID() {

    return teacherID;
}

string Section::getVenue() {

    return venueID;
}

Course* Section::getCourse() {

    return course;
}



string Section::getCourseType() {

    if (course != nullptr) {

        return course->getType();
    }

    return "Unknown";
}



bool Section::isFull() {

    if (studentCount >= capacity) {

        return true;
    }

    return false;
}

bool Section::addStudent(Student* s) {

    if (isFull()) {

        return false;
    }

    students[studentCount] = s;

    studentCount++;

    return true;
}

int Section::getStudentCount() {

    return studentCount;
}

// =====================================================
// DISPLAY
// =====================================================

void Section::displaySection() {

    cout << "\n===== SECTION =====\n";

    cout << "Section ID: "
        << sectionID
        << endl;

    cout << "Course ID: "
        << courseID
        << endl;

    cout << "Teacher ID: "
        << teacherID
        << endl;

    cout << "Venue: "
        << venueID
        << endl;

    cout << "Time Slot: "
        << timeSlot
        << endl;

    cout << "Course Type: "
        << getCourseType()
        << endl;

    cout << "Students Enrolled: "
        << studentCount
        << endl;
}