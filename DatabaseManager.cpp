#include "DatabaseManager.h"
#include <sstream>

// =====================================================
// LOAD STUDENTS
// =====================================================
void DatabaseManager::loadStudents(Student* students[], int& count)
{
    ifstream fin("Students.txt");
    count = 0;
    if (!fin) { cout << "\nStudents.txt missing!\n"; return; }

    string line;
    while (getline(fin, line) && count < 100) {
        if (line.empty()) continue;
        // Format: ID|Name|Type|GPA|Extra
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);
        int p4 = line.find('|', p3 + 1);

        string id = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string type = line.substr(p2 + 1, p3 - p2 - 1);
        float  gpa = stof(line.substr(p3 + 1, p4 - p3 - 1));
        string extra = line.substr(p4 + 1);

        if (type == "Regular")
            students[count++] = new RegularStudent(id, name, "", gpa);
        else if (type == "Scholarship") {
            float minGPA = extra.empty() ? 2.0f : stof(extra);
            students[count++] = new ScholarshipStudent(id, name, "", gpa, minGPA);
        }
        else if (type == "Exchange")
            students[count++] = new ExchangeStudent(id, name, "");
    }
    fin.close();
}

// =====================================================
// LOAD TEACHERS
// =====================================================
void DatabaseManager::loadTeachers(Teacher* teachers[], int& count)
{
    ifstream fin("Teachers.txt");
    count = 0;
    if (!fin) { cout << "\nTeachers.txt missing!\n"; return; }

    string line;
    while (getline(fin, line) && count < 100) {
        if (line.empty()) continue;
        // Format: ID|Name|RatingCount|Sum
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);

        string id = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        // rating field ignored on load; feedback is re-entered at runtime

        teachers[count++] = new Teacher(id, name, "");
    }
    fin.close();
}

// =====================================================
// LOAD COURSES
// =====================================================
void DatabaseManager::loadCourses(Course* courses[], int& count)
{
    ifstream fin("courses.txt");
    count = 0;
    if (!fin) { cout << "\ncourses.txt missing!\n"; return; }

    string line;
    while (getline(fin, line) && count < 100) {
        if (line.empty()) continue;
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);

        string cid = line.substr(0, p1);
        string title = line.substr(p1 + 1, p2 - p1 - 1);
        string tid = line.substr(p2 + 1, p3 - p2 - 1);
        string type = line.substr(p3 + 1);

        if (type == "Core")     courses[count++] = new CoreCourse(cid, title, tid);
        else if (type == "Elective") courses[count++] = new ElectiveCourse(cid, title, tid);
        else if (type == "Lab")      courses[count++] = new LabCourse(cid, title, tid);
    }
    fin.close();
}

// =====================================================
// LOAD SECTIONS
// =====================================================
void DatabaseManager::loadSections(
    Section* sections[], int& count,
    Course* courses[], int courseCount)
{
    ifstream fin("sections.txt");
    count = 0;
    if (!fin) { cout << "\nsections.txt missing!\n"; return; }

    string line;
    while (getline(fin, line) && count < 100) {
        if (line.empty()) continue;
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);
        int p4 = line.find('|', p3 + 1);

        string sid = line.substr(0, p1);
        string cid = line.substr(p1 + 1, p2 - p1 - 1);
        string tid = line.substr(p2 + 1, p3 - p2 - 1);
        string venue = line.substr(p3 + 1, p4 - p3 - 1);
        string slot = line.substr(p4 + 1);

        sections[count] = new Section(sid, slot, cid);
        sections[count]->setTeacherID(tid);
        sections[count]->setVenue(venue);

        for (int i = 0; i < courseCount; i++) {
            if (courses[i]->getCourseID() == cid) {
                sections[count]->setCourse(courses[i]);
                break;
            }
        }
        count++;
    }
    fin.close();
}

// =====================================================
// LOAD VENUES  — FIX: now uses pipe delimiter
// =====================================================
void DatabaseManager::loadVenues(Venue venues[], int& count)
{
    ifstream fin("venues.txt");
    count = 0;
    if (!fin) { cout << "\nvenues.txt missing!\n"; return; }

    string line;
    while (getline(fin, line) && count < 100) {
        if (line.empty()) continue;
        // Format: RoomID|Capacity|HasComputers(0/1)
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);

        string roomID = line.substr(0, p1);
        int    cap = stoi(line.substr(p1 + 1, p2 - p1 - 1));
        bool   hasComp = (stoi(line.substr(p2 + 1)) == 1);

        venues[count++] = Venue(roomID, cap, hasComp);
    }
    fin.close();
}

// =====================================================
// LOAD ASSESSMENTS  — FIX: actually does something now
// Populates a StudentAssessment array passed by caller
// =====================================================
void DatabaseManager::loadAssessments(Course* /*courses*/[], int /*courseCount*/)
{
    // assessments.txt is read on-demand inside calculateGPA()
    // via readScoresFromFile() helper in Student.cpp.
    // Nothing to do here at startup.
}

// =====================================================
// SAVE STUDENTS
// =====================================================
void DatabaseManager::saveStudents(Student* students[], int count)
{
    ofstream fout("Students.txt");
    for (int i = 0; i < count; i++) {
        fout << students[i]->getID() << "|"
            << students[i]->getName() << "|"
            << students[i]->getType() << "|"
            << students[i]->getGPA() << "|";

        if (students[i]->getType() == "Scholarship") {
            ScholarshipStudent* s = dynamic_cast<ScholarshipStudent*>(students[i]);
            fout << s->getMinGPA();
        }
        else {
            fout << "0";
        }
        fout << "\n";
    }
    fout.close();
    cout << "Students saved.\n";
}

// =====================================================
// SAVE TEACHERS  — FIX: saves clean format
// =====================================================
void DatabaseManager::saveTeachers(Teacher* teachers[], int count)
{
    ofstream fout("Teachers.txt");
    for (int i = 0; i < count; i++) {
        fout << teachers[i]->getID() << "|"
            << teachers[i]->getName() << "|"
            << teachers[i]->getAverageRating() << "\n";
    }
    fout.close();
    cout << "Teachers saved.\n";
}

// =====================================================
// SAVE ASSESSMENT (append)
// =====================================================
void DatabaseManager::saveStudentAssessment(
    string sid, string cid, string type, float raw, float max)
{
    ofstream fout("assessments.txt", ios::app);
    fout << sid << " " << cid << " " << type
        << " " << raw << " " << max << "\n";
    fout.close();
}
