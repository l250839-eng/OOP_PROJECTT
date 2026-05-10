#include "Teacher.h"



Teacher::Teacher(string id, string n, string e) {

    ID = id;
    name = n;
    email = e;

    count = 0;
}



void Teacher::addFeedback(int rating, string comment) {

    if (count >= 50) {
        cout << "Feedback limit reached!\n";
        return;
    }

    if (rating < 1) rating = 1;
    if (rating > 5) rating = 5;

    ratings[count] = rating;
    comments[count] = comment;

    count++;
}



double Teacher::getAverageRating() {

    if (count == 0)
        return 0;

    double sum = 0;

    for (int i = 0; i < count; i++) {
        sum += ratings[i];
    }

    return sum / count;
}



void Teacher::displayProfile() {

    cout << "\n===== TEACHER PROFILE =====\n";
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Avg Rating: " << getAverageRating() << endl;
}



void Teacher::displayFeedback() {

    cout << "\n===== TEACHER FEEDBACK =====\n";

    if (count == 0) {
        cout << "No feedback available.\n";
        return;
    }

    for (int i = 0; i < count; i++) {

        cout << "Rating: " << ratings[i]
            << " | Comment: " << comments[i]
            << endl;
    }
}



string Teacher::getID() {
    return ID;
}

string Teacher::getName() {
    return name;
}