#ifndef STUDENTASSESSMENT_H
#define STUDENTASSESSMENT_H

#include <string>
using namespace std;

class StudentAssessment {

private:

    string studentID;
    string courseID;
    string type;

    float rawScore;
    float maxScore;

public:

    StudentAssessment() {

        studentID = "";
        courseID = "";
        type = "";

        rawScore = 0;
        maxScore = 0;
    }

    StudentAssessment(
        string sid,
        string cid,
        string t,
        float raw,
        float max
    ) {

        studentID = sid;
        courseID = cid;
        type = t;

        rawScore = raw;
        maxScore = max;
    }

    string getStudentID() {

        return studentID;
    }

    string getCourseID() {

        return courseID;
    }

    string getType() {

        return type;
    }

    float getRawScore() {

        return rawScore;
    }

    float getMaxScore() {

        return maxScore;
    }

    float getPercentage() {

        return (rawScore / maxScore) * 100;
    }
};

#endif