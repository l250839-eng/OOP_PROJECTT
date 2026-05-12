#include "Section.h"
#include <iostream>
using namespace std;

// =====================================================
// CONSTRUCTOR
// =====================================================
Section::Section(string id, string time, string cid) {
    sectionID = id;
    timeSlot = time;
    courseID = cid;
    teacherID = "";
    venueID = "";
    course = nullptr;
    studentCount = 0;
    capacity = 50;   // default; override via setCapacity()
    for (int i = 0; i < 50; i++)
        students[i] = nullptr;
}

// =====================================================
// SETTERS
// =====================================================
void Section::setCourse(Course* c) { course = c; }
void Section::setVenue(string v) { venueID = v; }
void Section::setTeacherID(string id) { teacherID = id; }
void Section::setCapacity(int cap) { capacity = cap; }

// =====================================================
// GETTERS
// =====================================================
string  Section::getSectionID() { return sectionID; }
string  Section::getTimeSlot() { return timeSlot; }
string  Section::getCourseID() { return courseID; }
string  Section::getTeacherID() { return teacherID; }
string  Section::getVenue() { return venueID; }
Course* Section::getCourse() { return course; }

string Section::getCourseType()
{
    if (course != nullptr)
    {
        return course->getCourseType();
    }

    return "Unknown";
}
// =====================================================
// STUDENT MANAGEMENT
// =====================================================
bool Section::isFull() {
    return (studentCount >= capacity);
}

bool Section::addStudent(Student* s) {
    if (s == nullptr || isFull()) return false;
    students[studentCount++] = s;
    return true;
}

int Section::getStudentCount() {
    return studentCount;
}

// FIX: allows RegistrationManager to inspect who is in a section
Student* Section::getStudentAt(int index) {
    if (index < 0 || index >= studentCount) return nullptr;
    return students[index];
}

// =====================================================
// DISPLAY
// =====================================================
void Section::displaySection() {
    cout << "\n===== SECTION =====\n";
    cout << "Section ID : " << sectionID << "\n";
    cout << "Course ID  : " << courseID << "\n";
    cout << "Teacher ID : " << teacherID << "\n";
    cout << "Venue      : " << venueID << "\n";
    cout << "Time Slot  : " << timeSlot << "\n";
    cout << "Course Type: " << getCourseType() << "\n";
    cout << "Enrolled   : " << studentCount
        << " / " << capacity << "\n";
}
