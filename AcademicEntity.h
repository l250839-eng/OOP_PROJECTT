#pragma once

#include <iostream>
#include <string>
using namespace std;

class AcademicEntity
{
protected:
    string Id;
    string name;
    string email;

public:
    
    AcademicEntity(const string& id,
        const string& name,
        const string& email);

    
    virtual void displayProfile() = 0;

   
    string getID() const;
    string getName() const;
    string getEmail() const;

    virtual ~AcademicEntity() {}
};