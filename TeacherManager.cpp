
#include "TeacherManager.h"

// ================= CONSTRUCTOR =================
TeacherManager::TeacherManager() {

    count = 0;

    for (int i = 0; i < 100; i++) {
        teachers[i] = nullptr;
    }
}

// ================= ADD =================
bool TeacherManager::addTeacher(Teacher* t) {

    if (t == nullptr)
        return false;

    // -------- DUPLICATE CHECK --------
    for (int i = 0; i < count; i++) {

        if (teachers[i] != nullptr &&
            teachers[i]->getID() == t->getID()) {

            cout << "Teacher already exists!\n";
            return false;
        }
    }

    if (count >= 100) {
        cout << "Teacher limit reached!\n";
        return false;
    }

    teachers[count] = t;
    count++;

    return true;
}

// ================= SEARCH =================
Teacher* TeacherManager::searchTeacher(string id) {

    for (int i = 0; i < count; i++) {

        if (teachers[i] != nullptr &&
            teachers[i]->getID() == id) {

            return teachers[i];
        }
    }

    return nullptr;
}

// ================= DISPLAY =================
void TeacherManager::displayAllTeachers() {

    if (count == 0) {
        cout << "No Teachers Found!\n";
        return;
    }

    for (int i = 0; i < count; i++) {

        if (teachers[i] != nullptr) {
            teachers[i]->displayProfile();
        }
    }
}

// ================= CLEAR =================
void TeacherManager::clear() {

    for (int i = 0; i < count; i++) {
        teachers[i] = nullptr;
    }

    count = 0;
}

// ================= GET COUNT =================
int TeacherManager::getCount() {
    return count;
}