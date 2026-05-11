#ifndef ACADEMICENTITY_H
#define ACADEMICENTITY_H

#include <string>
using namespace std;

class AcademicEntity {

protected:

    string ID;
    string name;
    string email;

public:

    AcademicEntity(string id = "",
        string name = "",
        string email = "");

    string getID();
    string getName();
    string getEmail();   

    virtual void displayProfile() = 0;
};

#endif