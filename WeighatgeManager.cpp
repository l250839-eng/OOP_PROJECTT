#include "WeighatgeManager.h"

WeightageManager::WeightageManager() {
    count = 0;
}

// ================= LOAD FILE =================
void WeightageManager::loadFromFile(string filename) {

    ifstream file(filename);

    count = 0;

    while (file >> type[count] >> exam[count] >> assignment[count] >> quiz[count]) {
        count++;
    }

    file.close();
}

// ================= GET EXAM =================
int WeightageManager::getExamWeight(string courseType) {

    for (int i = 0; i < count; i++) {
        if (type[i] == courseType)
            return exam[i];
    }

    return 0;
}

// ================= GET ASSIGNMENT =================
int WeightageManager::getAssignmentWeight(string courseType) {

    for (int i = 0; i < count; i++) {
        if (type[i] == courseType)
            return assignment[i];
    }

    return 0;
}

// ================= GET QUIZ =================
int WeightageManager::getQuizWeight(string courseType) {

    for (int i = 0; i < count; i++) {
        if (type[i] == courseType)
            return quiz[i];
    }

    return 0;
}