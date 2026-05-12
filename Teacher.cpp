#include "Teacher.h"
#include <cctype>
// =====================================================
// CONSTRUCTOR
// =====================================================

Teacher::Teacher(string id,
    string n,
    string e)
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

    rating = 0;

    commentCount = 0;

    courseCount = 0;
}

// =====================================================
// FEEDBACK
// =====================================================

void Teacher::addFeedback(double score,
    string comment) {

    
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

    
    if (commentCount > 0) {

        cout << "\nComments:\n";

        for (int i = 0; i < commentCount; i++) {

            cout << "- "
                << comments[i]
                << endl;
        }
    }

    
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
float Teacher::getAverageFeedback()
{
    return averageFeedback;
}