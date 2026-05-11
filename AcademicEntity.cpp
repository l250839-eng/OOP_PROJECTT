#include "AcademicEntity.h"

AcademicEntity::AcademicEntity(string id,
    string name,
    string email) {

    this->ID = id;
    this->name = name;
    this->email = email;
}

string AcademicEntity::getID() {
    return ID;
}

string AcademicEntity::getName() {
    return name;
}

string AcademicEntity::getEmail() {
    return email;
}