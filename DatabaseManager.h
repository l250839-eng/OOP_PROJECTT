
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Section.h"
#include "Venue.h"
using namespace std;

class DatabaseManager {
public:
    // ---- Students ----
    void saveStudents(Student* students[], int count);
    void loadStudents(Student* students[], int& count);

    // ---- Teachers ----
    void saveTeachers(Teacher* teachers[], int count);
    void loadTeachers(Teacher* teachers[], int& count);

    // ---- Courses ----
    void saveCourses(Course* courses[], int count);
    void loadCourses(Course* courses[], int& count);

    // ---- Sections ----
    void saveSections(Section* sections[], int count);
    void loadSections(Section* sections[], int& count);

    // ---- Venues ----
    void saveVenues(Venue venues[], int count);
    void loadVenues(Venue venues[], int& count);

    // ---- Assessments (FIX: was missing entirely) ----
    // Saves all assessments from every course's Assessment* array.
    // Format per line:  CourseID | Type | RawScore | MaxScore
    void saveAssessments(Course* courses[], int courseCount);

    // Loads assessments.txt and re-attaches each Assessment* to the
    // matching Course object in the courses[] array.
    void loadAssessments(Course* courses[], int courseCount);

    // ---- Linkage ----
    void linkSectionsToCourses(Course* courses[], int courseCount,
        Section* sections[], int sectionCount);
    void saveStudentAssessment(
        string sid,
        string cid,
        string type,
        float raw,
        float max
    );

    float calculateStudentGrade(
        string sid,
        string cid,
        string courseType
    );
};

#endif
