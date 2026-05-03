#include "AcademicEntity.h"


  
AcademicEntity::AcademicEntity(const string& id,
    const string& name,
    const string& email)
{
    this->Id = id;
    this->name = name;
    this->email = email;
}


   

string AcademicEntity::getID() const {
    return Id;
}

string AcademicEntity::getName() const {
    return name;
}

string AcademicEntity::getEmail() const {
    return email;
}