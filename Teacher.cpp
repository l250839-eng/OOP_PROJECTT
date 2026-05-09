#include "Teacher.h"
#include <iostream>
using namespace std;

Teacher::Teacher(string id, string n, string e, double f)
    : AcademicEntity(id, n, e) {
    averageFeedback = f;
}

void Teacher::addFeedback(double rating) {
    averageFeedback = (averageFeedback + rating) / 2.0;
}

double Teacher::getFeedback() {
    return averageFeedback;
}

void Teacher::displayProfile() {
    cout << "[Teacher] " << name
        << " | ID: " << ID
        << " | Avg Feedback: " << averageFeedback << endl;
}