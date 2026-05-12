#include "Teacher.h"
#include <cctype>

// =====================================================
// CONSTRUCTOR
// =====================================================
Teacher::Teacher(string id, string n, string e)
    : AcademicEntity(id, n, "")
{
    string generatedEmail = n;
    for (int i = 0; i < (int)generatedEmail.length(); i++) {
        generatedEmail[i] = tolower(generatedEmail[i]);
        if (generatedEmail[i] == ' ') generatedEmail[i] = '.';
    }
    email = generatedEmail + "@gmail.com";

    ratingCount = 0;
    commentCount = 0;
    courseCount = 0;

    for (int i = 0; i < 100; i++) ratings[i] = 0;
    for (int i = 0; i < 100; i++) comments[i] = "";
    for (int i = 0; i < 20; i++) assignedCourses[i] = "";
}

// =====================================================
// FIX: accumulate every rating, then compute true average
// =====================================================
void Teacher::addFeedback(double score, string comment)
{
    if (score < 1 || score > 5) {
        cout << "\nInvalid rating! Must be 1-5.\n";
        return;
    }
    if (ratingCount < 100) {
        ratings[ratingCount++] = score;
    }
    if (commentCount < 100) {
        comments[commentCount++] = comment;
    }
}

double Teacher::getAverageRating()
{
    if (ratingCount == 0) return 0.0;
    double total = 0;
    for (int i = 0; i < ratingCount; i++) total += ratings[i];
    return total / ratingCount;
}

float Teacher::getAverageFeedback()
{
    return (float)getAverageRating();
}

// =====================================================
// ASSIGN COURSE
// =====================================================
void Teacher::assignCourse(string cid)
{
    if (courseCount < 20)
        assignedCourses[courseCount++] = cid;
}

// =====================================================
// DISPLAY
// =====================================================
void Teacher::displayProfile()
{
    cout << "\n===== TEACHER PROFILE =====\n";
    cout << "ID         : " << ID << "\n";
    cout << "Name       : " << name << "\n";
    cout << "Email      : " << email << "\n";
    cout << "Avg Rating : ";
    if (ratingCount == 0)
        cout << "No ratings yet\n";
    else
        cout << getAverageRating() << " / 5  (" << ratingCount << " review(s))\n";

    if (commentCount > 0) {
        cout << "\nFeedback Comments:\n";
        for (int i = 0; i < commentCount; i++)
            cout << "  [" << i + 1 << "] " << comments[i] << "\n";
    }

    if (courseCount > 0) {
        cout << "\nAssigned Courses:\n";
        for (int i = 0; i < courseCount; i++)
            cout << "  - " << assignedCourses[i] << "\n";
    }
    cout << "\n";
}

// =====================================================
// GETTERS
// =====================================================
string Teacher::getID() { return ID; }
string Teacher::getName() { return name; }
string Teacher::getEmail() { return email; }
