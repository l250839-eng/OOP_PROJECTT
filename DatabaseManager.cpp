#include "DatabaseManager.h"

#include "CoreCourse.h"
#include "ElectiveCourse.h"
#include "LabCourse.h"

// =====================================================
// STUDENTS
// =====================================================


// =====================================================
// LOAD STUDENTS
// =====================================================

void DatabaseManager::loadStudents(Student* students[],
    int& count) {

    ifstream file("students.txt");

    string id;
    string name;
    string type;
    string extra;

    double gpa;

    count = 0;

    while (file >> id
        >> name
        >> type
        >> gpa
        >> extra) {

        // AUTO EMAIL
        string email =
            name + "@nu.edu.pk";

        // REGULAR
        if (type == "Regular") {

            students[count] =
                new RegularStudent(
                    id,
                    name,
                    email,
                    gpa
                );
        }

        // SCHOLARSHIP
        else if (type == "Scholarship") {

            double minGPA =
                stod(extra);

            students[count] =
                new ScholarshipStudent(
                    id,
                    name,
                    email,
                    gpa,
                    minGPA
                );
        }

        // EXCHANGE
        else if (type == "Exchange") {

            students[count] =
                new ExchangeStudent(
                    id,
                    name,
                    email
                );
        }

        count++;
    }

    file.close();
}
// =====================================================
// SAVE STUDENTS
// =====================================================
void DatabaseManager::saveStudents(Student* students[], int count) {
    ofstream file("students.txt");
    for (int i = 0; i < count; i++) {
        if (students[i] == nullptr) continue;

        string type = students[i]->getType();  // "Regular" / "Scholarship" / "Exchange"
        float  gpa = students[i]->getGPA();
        string extra = "-";

        if (type == "Scholarship") {
            // Cast to access minGPA via the new getter
            ScholarshipStudent* ss = static_cast<ScholarshipStudent*>(students[i]);
            extra = to_string(ss->getMinGPA());
        }
        else if (type == "Exchange") {
            extra = "PASS";   // matches the format loadStudents() skips over
        }

        file << students[i]->getID() << " "
            << students[i]->getName() << " "
            << type << " "
            << gpa << " "
            << extra
            << "\n";
    }
    file.close();
}
// =====================================================
// TEACHERS
// =====================================================

void DatabaseManager::saveTeachers(Teacher* teachers[],
    int count) {

    ofstream file("teachers.txt");

    for (int i = 0; i < count; i++) {

        if (teachers[i] != nullptr) {

            file << teachers[i]->getID() << " "
                << teachers[i]->getName() << " "
                << teachers[i]->getAverageRating()
                << endl;
        }
    }

    file.close();
}

// =====================================================
// LOAD TEACHERS
// =====================================================

void DatabaseManager::loadTeachers(Teacher* teachers[],
    int& count) {

    ifstream file("teachers.txt");

    string id;
    string name;

    double rating;

    count = 0;

    while (file >> id
        >> name
        >> rating) {

        // AUTO EMAIL
        string email =
            name + "@nu.edu.pk";

        Teacher* t =
            new Teacher(
                id,
                name,
                email
            );

        t->addFeedback(
            rating,
            "Loaded"
        );

        teachers[count] = t;

        count++;
    }

    file.close();
}

// =====================================================
// COURSES
// =====================================================

void DatabaseManager::saveCourses(Course* courses[],
    int count) {

    ofstream file("courses.txt");

    for (int i = 0; i < count; i++) {

        if (courses[i] != nullptr) {

            file << courses[i]->getCourseID() << " "
                << courses[i]->getTitle() << " "
                << courses[i]->getTeacherID() << " "

                << courses[i]->getType()
                << endl;
        }
    }

    file.close();
}

// =====================================================
// LOAD COURSES
// =====================================================

void DatabaseManager::loadCourses(Course* courses[],
    int& count) {

    ifstream file("courses.txt");

    string id;
    string title;
    string tid;
    string type;

    count = 0;

    while (file >> id
        >> title
        >> tid
        >> type) {

        if (type == "Core") {

            courses[count] =
                new CoreCourse(
                    id,
                    title,
                    tid
                );
        }

        else if (type == "Elective") {

            courses[count] =
                new ElectiveCourse(
                    id,
                    title,
                    tid
                );
        }

        else if (type == "Lab") {

            courses[count] =
                new LabCourse(
                    id,
                    title,
                    tid
                );
        }

        count++;
    }

    file.close();
}

// =====================================================
// SECTIONS
// =====================================================

void DatabaseManager::saveSections(Section* sections[],
    int count) {

    ofstream file("sections.txt");

    for (int i = 0; i < count; i++) {

        if (sections[i] != nullptr) {

            file << sections[i]->getSectionID() << " "
                << sections[i]->getCourseID() << " "
                << sections[i]->getTeacherID() << " "
                << sections[i]->getVenue() << " "
                << sections[i]->getTimeSlot()
                << endl;
        }
    }

    file.close();
}

// =====================================================
// LOAD SECTIONS
// =====================================================

void DatabaseManager::loadSections(Section* sections[],
    int& count) {

    ifstream file("sections.txt");

    string sid;
    string cid;
    string tid;
    string vid;
    string time;

    count = 0;

    while (file >> sid
        >> cid
        >> tid
        >> vid
        >> time) {

        Section* s =
            new Section(
                sid,
                time,
                cid
            );

        s->setTeacherID(tid);

        s->setVenue(vid);

        sections[count] = s;

        count++;
    }

    file.close();
}

// =====================================================
// VENUES
// =====================================================

void DatabaseManager::saveVenues(Venue venues[],
    int count) {

    ofstream file("venues.txt");

    for (int i = 0; i < count; i++) {

        file << venues[i].getRoomID() << " "
            << venues[i].getCapacity() << " "
            << venues[i].hasComputers()
            << endl;
    }

    file.close();
}

// =====================================================
// LOAD VENUES
// =====================================================

void DatabaseManager::loadVenues(Venue venues[],
    int& count) {

    ifstream file("venues.txt");

    string id;

    int cap;

    bool comp;

    count = 0;

    while (file >> id
        >> cap
        >> comp) {

        venues[count] =
            Venue(
                id,
                cap,
                comp
            );

        count++;
    }

    file.close();
}

// =====================================================
// LINK SECTION ? COURSE
// =====================================================

void DatabaseManager::linkSectionsToCourses(
    Course* courses[],
    int courseCount,
    Section* sections[],
    int sectionCount) {

    for (int i = 0; i < sectionCount; i++) {

        string cid =
            sections[i]->getCourseID();

        for (int j = 0; j < courseCount; j++) {

            if (courses[j]->getCourseID() == cid) {

                sections[i]->setCourse(
                    courses[j]
                );

                break;
            }
        }
    }
}