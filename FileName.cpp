#include <iostream>
#include <string>
#include <limits>

#include "DatabaseManager.h"
#include "RegistrationManager.h"
#include "Scheduler.h"
#include "WeighatgeManager.h"
#include "AdminManager.h"
#include "TeacherManager.h"

using namespace std;

static void clearInput()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void printSeparator(char c = '=', int w = 44)
{
    for (int i = 0; i < w; i++) cout << c;
    cout << "\n";
}

static void pause()
{
    cout << "\nPress Enter to continue...";
    clearInput();
    cin.get();
}


static void printMainMenu()
{
    printSeparator();
    cout << "    ACADEMIC OFFICE REPLACEMENT SYSTEM\n";
    printSeparator();
    cout << "  [ STUDENT ]\n";
    cout << "   1.  Display All Students\n";
    cout << "   2.  Add Student\n";
    cout << "   3.  Delete Student\n";
    cout << "   4.  View Student Transcript\n";
    cout << "   5.  Calculate Student GPA\n";
    cout << "\n  [ TEACHER ]\n";
    cout << "   6.  Display All Teachers\n";
    cout << "   7.  Add Teacher\n";
    cout << "   8.  Delete Teacher\n";
    cout << "   9.  Leave Teacher Feedback\n";
    cout << "\n  [ COURSES & SECTIONS ]\n";
    cout << "  10.  Display All Courses\n";
    cout << "  11.  Display All Sections\n";
    cout << "  12.  Register Student in Section\n";
    cout << "\n  [ GRADING ]\n";
    cout << "  13.  Enter Assessment Marks\n";
    cout << "\n  [ SCHEDULING ]\n";
    cout << "  14.  Run Venue Assignment\n";
    cout << "  15.  Check Schedule Conflicts\n";
    cout << "\n  [ SYSTEM ]\n";
    cout << "  16.  Save All Data\n";
    cout << "\n17.  Add course \n" ;
    cout << "   0.  Exit\n";
    printSeparator('-');
    cout << "  Choice: ";
}

// ?????????????????????????????????????????????????????
// MAIN
// ?????????????????????????????????????????????????????
int main()
{
   
    WeightageManager::get();

    DatabaseManager     db;
    RegistrationManager regManager;
    Scheduler           scheduler;

    Student* students[100];
    Teacher* teachers[100];
    Course* courses[100];
    Section* sections[100];
    Venue    venues[100];

    int studentCount = 0, teacherCount = 0;
    int courseCount = 0, sectionCount = 0, venueCount = 0;

    
    cout << "\nLoading data...\n";
    db.loadStudents(students, studentCount);
    db.loadTeachers(teachers, teacherCount);
    db.loadCourses(courses, courseCount);
    db.loadSections(sections, sectionCount, courses, courseCount);
    db.loadVenues(venues, venueCount);
    cout << "Loaded: "
        << studentCount << " students, "
        << teacherCount << " teachers, "
        << courseCount << " courses, "
        << sectionCount << " sections, "
        << venueCount << " venues.\n";

    int choice;

    do {
        printMainMenu();
        if (!(cin >> choice)) {
            cin.clear(); clearInput();
            cout << "\nInvalid input.\n";
            continue;
        }

        
        if (choice == 1) {
            printSeparator();
            cout << " ALL STUDENTS (" << studentCount << ")\n";
            printSeparator();
            if (studentCount == 0) cout << " No students found.\n";
            for (int i = 0; i < studentCount; i++)
                students[i]->displayProfile();
            pause();
        }

        else if (choice == 2) {
            if (studentCount >= 100) {
                cout << "\nStudent limit reached!\n"; pause(); continue;
            }
            string id, name, type;
            float  gpa;

            cout << "\nEnter Student ID   : "; cin >> id; clearInput();
            cout << "Enter Student Name : "; getline(cin, name);
            cout << "Enter Type (Regular/Scholarship/Exchange): "; cin >> type;

            // Duplicate ID check
            bool dup = false;
            for (int i = 0; i < studentCount; i++)
                if (students[i]->getID() == id) { dup = true; break; }
            if (dup) { cout << "\nStudent ID already exists!\n"; pause(); continue; }

            if (type == "Regular") {
                cout << "Enter GPA          : "; cin >> gpa;
                students[studentCount++] = new RegularStudent(id, name, "", gpa);
            }
            else if (type == "Scholarship") {
                float minGPA;
                cout << "Enter GPA          : "; cin >> gpa;
                cout << "Enter Min GPA      : "; cin >> minGPA;
                students[studentCount++] = new ScholarshipStudent(id, name, "", gpa, minGPA);
            }
            else if (type == "Exchange") {
                students[studentCount++] = new ExchangeStudent(id, name, "");
            }
            else { cout << "\nUnknown type!\n"; pause(); continue; }

            cout << "\nStudent added successfully!\n";
            pause();
        }

       
        else if (choice == 3) {
            string sid;
            cout << "\nEnter Student ID to delete: "; cin >> sid;

            bool found = false;
            for (int i = 0; i < studentCount; i++) {
                if (students[i]->getID() == sid) {
                    delete students[i];
                    for (int j = i; j < studentCount - 1; j++)
                        students[j] = students[j + 1];
                    studentCount--;
                    found = true;
                    cout << "\nStudent deleted.\n";
                    break;
                }
            }
            if (!found) cout << "\nStudent not found.\n";
            pause();
        }

       
        else if (choice == 4) {
            string sid;
            cout << "\nEnter Student ID: "; cin >> sid;

            Student* s = nullptr;
            for (int i = 0; i < studentCount; i++)
                if (students[i]->getID() == sid) { s = students[i]; break; }

            if (!s) cout << "\nStudent not found.\n";
            else    s->viewTranscript();
            pause();
        }

        
        
        else if (choice == 5) {
            string sid;
            cout << "\nEnter Student ID: "; cin >> sid;

            Student* s = nullptr;
            for (int i = 0; i < studentCount; i++)
                if (students[i]->getID() == sid) { s = students[i]; break; }

            if (!s) { cout << "\nStudent not found.\n"; pause(); continue; }

            s->calculateGPA();
            s->viewTranscript();
            pause();
        }

        // ???????????????????????????????????????????
        // 6. DISPLAY ALL TEACHERS
        // ???????????????????????????????????????????
        else if (choice == 6) {
            printSeparator();
            cout << " ALL TEACHERS (" << teacherCount << ")\n";
            printSeparator();
            if (teacherCount == 0) cout << " No teachers found.\n";
            for (int i = 0; i < teacherCount; i++)
                teachers[i]->displayProfile();
            pause();
        }

        // ???????????????????????????????????????????
        // 7. ADD TEACHER
        // ???????????????????????????????????????????
        else if (choice == 7) {
            if (teacherCount >= 100) {
                cout << "\nTeacher limit reached!\n"; pause(); continue;
            }
            string id, name;
            cout << "\nEnter Teacher ID   : "; cin >> id; clearInput();
            cout << "Enter Teacher Name : "; getline(cin, name);

            bool dup = false;
            for (int i = 0; i < teacherCount; i++)
                if (teachers[i]->getID() == id) { dup = true; break; }
            if (dup) { cout << "\nTeacher ID already exists!\n"; pause(); continue; }

            teachers[teacherCount++] = new Teacher(id, name, "");
            cout << "\nTeacher added successfully!\n";
            pause();
        }

        // ???????????????????????????????????????????
        // 8. DELETE TEACHER
        // ???????????????????????????????????????????
        else if (choice == 8) {
            string tid;
            cout << "\nEnter Teacher ID to delete: "; cin >> tid;

            bool found = false;
            for (int i = 0; i < teacherCount; i++) {
                if (teachers[i]->getID() == tid) {
                    delete teachers[i];
                    for (int j = i; j < teacherCount - 1; j++)
                        teachers[j] = teachers[j + 1];
                    teacherCount--;
                    found = true;
                    cout << "\nTeacher deleted.\n";
                    break;
                }
            }
            if (!found) cout << "\nTeacher not found.\n";
            pause();
        }

        // ???????????????????????????????????????????
        // 9. TEACHER FEEDBACK
        // ???????????????????????????????????????????
        else if (choice == 9) {
            string tid;
            cout << "\nEnter Teacher ID: "; cin >> tid; clearInput();

            Teacher* t = nullptr;
            for (int i = 0; i < teacherCount; i++)
                if (teachers[i]->getID() == tid) { t = teachers[i]; break; }

            if (!t) { cout << "\nTeacher not found.\n"; pause(); continue; }

            double rating;
            string comment;
            cout << "Enter Rating (1-5): "; cin >> rating; clearInput();
            cout << "Enter Comment     : "; getline(cin, comment);

            t->addFeedback(rating, comment);

            cout << "\nFeedback added. New average rating: "
                << t->getAverageRating() << " / 5\n";

            // Persist feedback to file
            ofstream fout("feedback.txt", ios::app);
            fout << tid << "|" << rating << "|" << comment << "\n";
            fout.close();
            pause();
        }

        // ???????????????????????????????????????????
        // 10. DISPLAY ALL COURSES
        // ???????????????????????????????????????????
        else if (choice == 10) {
            printSeparator();
            cout << " ALL COURSES (" << courseCount << ")\n";
            printSeparator();
            if (courseCount == 0) cout << " No courses found.\n";
            for (int i = 0; i < courseCount; i++) {
                courses[i]->displayCourse();
                cout << "\n";
            }
            pause();
        }

        // ???????????????????????????????????????????
        // 11. DISPLAY ALL SECTIONS
        // ???????????????????????????????????????????
        else if (choice == 11) {
            printSeparator();
            cout << " ALL SECTIONS (" << sectionCount << ")\n";
            printSeparator();
            if (sectionCount == 0) cout << " No sections found.\n";
            for (int i = 0; i < sectionCount; i++) {
                sections[i]->displaySection();
                cout << "\n";
            }
            pause();
        }

        // ???????????????????????????????????????????
        // 12. REGISTER STUDENT
        // ???????????????????????????????????????????
        else if (choice == 12) {
            string sid, secid;
            cout << "\nEnter Student ID : "; cin >> sid;
            cout << "Enter Section ID : "; cin >> secid;

            Student* s = nullptr;
            Section* sec = nullptr;

            for (int i = 0; i < studentCount; i++)
                if (students[i]->getID() == sid) { s = students[i]; break; }
            for (int i = 0; i < sectionCount; i++)
                if (sections[i]->getSectionID() == secid) { sec = sections[i]; break; }

            if (!s) { cout << "\nStudent not found.\n";   pause(); continue; }
            if (!sec) { cout << "\nSection not found.\n";   pause(); continue; }

            bool ok = regManager.registerStudent(s, sec, sections, sectionCount);
            if (ok) {
                sec->addStudent(s);
                s->enrollCourse(sec->getCourse());
                cout << "Registration complete.\n";
            }
            pause();
        }

        
        else if (choice == 13) {
            string sid, cid, type;
            float  raw, max;

            cout << "\nEnter Student ID         : "; cin >> sid;
            cout << "Enter Course ID          : "; cin >> cid;

            
            bool sOK = false, cOK = false;
            for (int i = 0; i < studentCount; i++)
                if (students[i]->getID() == sid) { sOK = true; break; }
            for (int i = 0; i < courseCount; i++)
                if (courses[i]->getCourseID() == cid) { cOK = true; break; }

            if (!sOK) { cout << "\nStudent not found!\n"; pause(); continue; }
            if (!cOK) { cout << "\nCourse not found!\n";  pause(); continue; }

            cout << "Enter Type (Exam/Assignment/Quiz): "; cin >> type;
            cout << "Enter Raw Score               : "; cin >> raw;
            cout << "Enter Max Score               : "; cin >> max;

            if (max <= 0) { cout << "\nMax score must be > 0.\n"; pause(); continue; }
            if (raw < 0 || raw > max) {
                cout << "\nRaw score must be between 0 and max.\n"; pause(); continue;
            }

            db.saveStudentAssessment(sid, cid, type, raw, max);

            cout << "\nAssessment saved. (" << raw << "/" << max
                << " = " << (raw / max * 100) << "%)\n";
            pause();
        }

        // ???????????????????????????????????????????
        // 14. RUN VENUE ASSIGNMENT
        // ???????????????????????????????????????????
        else if (choice == 14) {
            if (sectionCount == 0) {
                cout << "\nNo sections loaded.\n"; pause(); continue;
            }
            if (venueCount == 0) {
                cout << "\nNo venues loaded.\n"; pause(); continue;
            }
            scheduler.assignVenues(sections, sectionCount, venues, venueCount);
            pause();
        }

        // ???????????????????????????????????????????
        // 15. CHECK CONFLICTS
        // ???????????????????????????????????????????
        else if (choice == 15) {
            scheduler.checkConflict(sections, sectionCount);
            pause();
        }

        // ???????????????????????????????????????????
        // 16. SAVE ALL DATA
        // ???????????????????????????????????????????
        else if (choice == 16) {
            db.saveStudents(students, studentCount);
            db.saveTeachers(teachers, teacherCount);
            cout << "\nAll data saved successfully.\n";
            pause();
        }

      

        // ???????????????????????????????????????????
// 17. ADD COURSE
// ???????????????????????????????????????????
        else if (choice == 17)
        {
            if (courseCount >= 100) {
                cout << "\nCourse limit reached!\n"; pause(); continue;
            }

            string cid, title, tid, type;

            cout << "\nEnter Course ID       : "; cin >> cid; clearInput();
            cout << "Enter Title           : "; getline(cin, title);
            cout << "Enter Teacher ID      : "; cin >> tid;
            cout << "Enter Type (Core/Elective/Lab): "; cin >> type;

          
            bool dup = false;
            for (int i = 0; i < courseCount; i++)
                if (courses[i]->getCourseID() == cid) { dup = true; break; }
            if (dup) { cout << "\nCourse ID already exists!\n"; pause(); continue; }

            if (type == "Core")
                courses[courseCount++] = new CoreCourse(cid, title, tid);
            else if (type == "Elective")
                courses[courseCount++] = new ElectiveCourse(cid, title, tid);
            else if (type == "Lab")
                courses[courseCount++] = new LabCourse(cid, title, tid);
            else { cout << "\nUnknown type! Use Core, Elective, or Lab.\n"; pause(); continue; }

            
            ofstream fout("courses.txt", ios::app);
            fout << cid << "|" << title << "|" << tid << "|" << type << "\n";
            fout.close();

            cout << "\nCourse added and saved successfully!\n";
            pause();
            }

        else if (choice != 0) {
            cout << "\nInvalid choice. Please try again.\n";
        }



    } while (choice != 0);

    cout << "\nExiting system. Goodbye!\n";

    
    for (int i = 0; i < studentCount; i++) delete students[i];
    for (int i = 0; i < teacherCount; i++) delete teachers[i];
    for (int i = 0; i < courseCount; i++) delete courses[i];
    for (int i = 0; i < sectionCount; i++) delete sections[i];

    return 0;
}
