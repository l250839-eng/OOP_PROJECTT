#include "AdminManager.h"


AdminManager::AdminManager() {

    count = 0;

    for (int i = 0; i < 100; i++) {
        students[i] = nullptr;
    }
}

// ================= ADD STUDENT =================
bool AdminManager::addStudent(Student* s) {

    if (s == nullptr)
        return false;

    // -------- DUPLICATE CHECK --------
    for (int i = 0; i < count; i++) {

        if (students[i] != nullptr &&
            students[i]->getID() == s->getID()) {

            cout << "Student already exists!\n";
            return false;
        }
    }

    // -------- CAPACITY CHECK --------
    if (count >= 100) {
        cout << "Student limit reached!\n";
        return false;
    }

    students[count] = s;
    count++;

    return true;
}

// ================= SEARCH =================
Student* AdminManager::searchStudent(string id) {

    for (int i = 0; i < count; i++) {

        if (students[i] != nullptr &&
            students[i]->getID() == id) {

            return students[i];
        }
    }

    return nullptr;
}

// ================= DISPLAY =================
void AdminManager::displayAllStudents() {

    if (count == 0) {
        cout << "No Students Found!\n";
        return;
    }

    for (int i = 0; i < count; i++) {

        if (students[i] != nullptr) {
            students[i]->displayProfile();
        }
    }
}

// ================= CLEAR =================
void AdminManager::clear() {

    for (int i = 0; i < count; i++) {
        students[i] = nullptr;
    }

    count = 0;
}

// ================= GET COUNT =================
int AdminManager::getCount() {
    return count;
}