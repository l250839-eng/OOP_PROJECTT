#include "Teacher.h"

// =====================================================
// CONSTRUCTOR
// =====================================================

Teacher::Teacher(string id,
    string n,
    string e)
    : AcademicEntity(id, n, e) {

    rating = 0;

    commentCount = 0;

    courseCount = 0;
}

// =====================================================
// FEEDBACK
// =====================================================

void Teacher::addFeedback(double score,
    string comment) {

    // REPLACE OLD RATING
    rating = score;

    comments[commentCount] = comment;

    commentCount++;
}

// =====================================================
// GET RATING
// =====================================================

double Teacher::getAverageRating() {

    return rating;
}

// =====================================================
// ASSIGN COURSE
// =====================================================

void Teacher::assignCourse(string cid) {

    assignedCourses[courseCount] = cid;

    courseCount++;
}

// =====================================================
// DISPLAY PROFILE
// =====================================================

void Teacher::displayProfile() {

    cout << "\n===== TEACHER PROFILE =====\n";

    cout << "ID: "
        << ID
        << endl;

    cout << "Name: "
        << name
        << endl;

    cout << "Email: "
        << email
        << endl;

    cout << "Avg Rating: "
        << rating
        << endl;

    // SHOW COMMENTS
    if (commentCount > 0) {

        cout << "\nComments:\n";

        for (int i = 0; i < commentCount; i++) {

            cout << "- "
                << comments[i]
                << endl;
        }
    }

    // SHOW COURSES
    if (courseCount > 0) {

        cout << "\nAssigned Courses:\n";

        for (int i = 0; i < courseCount; i++) {

            cout << assignedCourses[i]
                << endl;
        }
    }

    cout << endl;
}

// =====================================================
// GETTERS
// =====================================================

string Teacher::getID() {

    return ID;
}

string Teacher::getName() {

    return name;
}

string Teacher::getEmail() {

    return email;
}