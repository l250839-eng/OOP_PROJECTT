#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include "Assessment.h"
using namespace std;

// Max assessments stored per course
#define MAX_ASSESSMENTS 30

class Course {
protected:
    string courseID;
    string title;
    string teacherID;

    // Spec requirement: pointer-array of Assessment*
    Assessment* assessments[MAX_ASSESSMENTS];
    int assessmentCount;

public:
    Course();
    Course(string cid, string t, string tid);

    // Pure virtuals — each course type implements its own weightage logic
    virtual float calculateFinalGrade(float exam, float assignment, float quiz) = 0;
    virtual int   getExamDuration() = 0;
    virtual string getType() = 0;

    // Assessment management
    void   addAssessment(Assessment* a);
    // Calculates final grade using the stored Assessment* array + virtual weightages
    float  calculateFinalGradeFromAssessments();
    void   clearAssessments();
    int    getAssessmentCount();
    Assessment* getAssessment(int index);

    string getCourseID();
    string getTeacherID();
    string getTitle();

    virtual ~Course();
};

#endif
