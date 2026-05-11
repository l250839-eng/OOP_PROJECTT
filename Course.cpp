#include "Course.h"

// =====================================================
// BASE COURSE
// =====================================================

Course::Course() {

}

Course::Course(
    string cid,
    string t,
    string tid
) {

    courseID = cid;
    title = t;
    teacherID = tid;
}

string Course::getCourseID() {

    return courseID;
}

string Course::getTitle() {

    return title;
}

string Course::getTeacherID() {

    return teacherID;
}




