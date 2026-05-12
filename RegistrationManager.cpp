#include "RegistrationManager.h"



bool RegistrationManager::registerStudent(Student* student, Section* section) {

    if (student == nullptr || section == nullptr) {
        return false;
    }

   
    for (int i = 0; i < section->getStudentCount(); i++) {

    }

    // ---------------- ADD STUDENT ----------------
    section->addStudent(student);

    cout << "Student " << student->getID()
        << " registered in section "
        << section->getSectionID() << endl;

    return true;
}

// =====================================================
// CONFLICT CHECK
// =====================================================

bool RegistrationManager::hasConflict(Section* s1, Section* s2) {

    if (s1 == nullptr || s2 == nullptr) {
        return false;
    }

   
    if (s1->getTimeSlot() == s2->getTimeSlot() &&
        s1->getVenue() == s2->getVenue()) {

        return true;
    }

    return false;
}