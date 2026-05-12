#include "WeighatgeManager.h"

WeightageManager* WeightageManager::instance = nullptr;

WeightageManager::WeightageManager()
{
    count = 0;
    loadFromFile("weightages.txt");
}

WeightageManager& WeightageManager::get()
{
    if (!instance) instance = new WeightageManager();
    return *instance;
}

void WeightageManager::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "\nweightages.txt missing! Using defaults.\n";
        // Defaults matching the spec
        courseTypes[0] = "Core";    examW[0] = 0.70f; assignW[0] = 0.20f; quizW[0] = 0.10f;
        courseTypes[1] = "Elective"; examW[1] = 0.50f; assignW[1] = 0.30f; quizW[1] = 0.20f;
        courseTypes[2] = "Lab";     examW[2] = 0.00f; assignW[2] = 0.70f; quizW[2] = 0.30f;
        count = 3;
        return;
    }

    count = 0;
    string line;
    while (getline(file, line) && count < 10) {
        if (line.empty()) continue;
        // Format: Core|70|20|10   (percentages as integers)
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);
        if (p1 == (int)string::npos) continue;

        courseTypes[count] = line.substr(0, p1);
        examW[count] = stof(line.substr(p1 + 1, p2 - p1 - 1)) / 100.0f;
        assignW[count] = stof(line.substr(p2 + 1, p3 - p2 - 1)) / 100.0f;
        quizW[count] = stof(line.substr(p3 + 1)) / 100.0f;
        count++;
    }
    file.close();
}

float WeightageManager::getExamWeight(string t) {
    for (int i = 0; i < count; i++) if (courseTypes[i] == t) return examW[i];
    return 0.5f;
}
float WeightageManager::getAssignmentWeight(string t) {
    for (int i = 0; i < count; i++) if (courseTypes[i] == t) return assignW[i];
    return 0.3f;
}
float WeightageManager::getQuizWeight(string t) {
    for (int i = 0; i < count; i++) if (courseTypes[i] == t) return quizW[i];
    return 0.2f;
}
