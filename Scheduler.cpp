#include "Scheduler.h"
#include "Section.h"
#include <iostream>
#include <fstream>
using namespace std;

// Available exam time windows (linear pool)
static const char* TIME_WINDOWS[] = {
    "Mon 8AM", "Mon 11AM", "Mon 2PM",
    "Tue 8AM", "Tue 11AM", "Tue 2PM",
    "Wed 8AM", "Wed 11AM", "Wed 2PM",
    "Thu 8AM", "Thu 11AM", "Thu 2PM"
};
static const int WINDOW_COUNT = 12;

// ?????????????????????????????????????????????????????
// assignVenues: match each section to a suitable venue
// and assign an exam time slot.
// Rules:
//   1. Venue capacity >= section student count
//   2. LabCourse requires hasComputers == true
//   3. No two sections in the same venue at same time
//   4. Conflict Solver: if a slot is taken, linearly
//      scan to the next free (venue, slot) pair
// ?????????????????????????????????????????????????????
void Scheduler::assignVenues(
    Section* sections[], int sectionCount,
    Venue    venues[], int venueCount)
{
    // Track which (venueIdx, windowIdx) pairs are occupied
    bool occupied[100][12] = {};   // [venue][window]

    cout << "\n========== VENUE ASSIGNMENT ==========\n";

    for (int i = 0; i < sectionCount; i++) {
        Section* sec = sections[i];
        bool     needPC = (sec->getCourseType() == "Lab");
        int      needed = sec->getStudentCount();

        // If section has no students yet, treat as 1 for scheduling
        if (needed == 0) needed = 1;

        bool assigned = false;

        for (int w = 0; w < WINDOW_COUNT && !assigned; w++) {
            for (int v = 0; v < venueCount && !assigned; v++) {

                // Capacity check
                if (venues[v].getCapacity() < needed) continue;

                // Computer lab check
                if (needPC && !venues[v].hasComputers()) continue;

                // Occupation check
                if (occupied[v][w]) continue;

                // ?? ASSIGN ??
                occupied[v][w] = true;
                sec->setVenue(venues[v].getRoomID());

                cout << "Section " << sec->getSectionID()
                    << "  ->  Venue: " << venues[v].getRoomID()
                    << "  |  Slot: " << TIME_WINDOWS[w]
                    << "  |  Seats: " << needed
                    << "/" << venues[v].getCapacity();
                if (needPC) cout << "  [LAB]";
                cout << "\n";

                assigned = true;
            }
        }

        if (!assigned) {
            cout << "WARNING: No suitable venue found for section "
                << sec->getSectionID() << "!\n";
        }
    }

    // Save schedule to file
    ofstream fout("exam_schedule.txt");
    fout << "SectionID | Venue | TimeSlot | Students\n";
    fout << "-------------------------------------------\n";
    for (int i = 0; i < sectionCount; i++) {
        fout << sections[i]->getSectionID() << " | "
            << sections[i]->getVenue() << " | "
            << sections[i]->getTimeSlot() << " | "
            << sections[i]->getStudentCount() << "\n";
    }
    fout.close();

    cout << "\nExam schedule saved to exam_schedule.txt\n";
    cout << "==========================================\n";
}

// ?????????????????????????????????????????????????????
// checkConflict: reports every (venue, time) collision
// and suggests the next free time slot (Conflict Solver)
// ?????????????????????????????????????????????????????
bool Scheduler::checkConflict(Section* sections[], int count)
{
    bool anyConflict = false;

    cout << "\n========== CONFLICT CHECK ==========\n";

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (sections[i]->getVenue() == sections[j]->getVenue() &&
                sections[i]->getTimeSlot() == sections[j]->getTimeSlot())
            {
                cout << "CONFLICT: Section " << sections[i]->getSectionID()
                    << " and Section " << sections[j]->getSectionID()
                    << "  both at [" << sections[i]->getTimeSlot()
                    << "] in venue [" << sections[i]->getVenue() << "]\n";

                // ?? CONFLICT SOLVER: find next free slot for section j ??
                string currentSlot = sections[j]->getTimeSlot();
                int    nextWindow = -1;
                for (int w = 0; w < WINDOW_COUNT; w++) {
                    if (TIME_WINDOWS[w] == currentSlot) {
                        nextWindow = w + 1;
                        break;
                    }
                }

                // Find a free window at the same venue
                bool solved = false;
                for (int w = nextWindow; w < WINDOW_COUNT && !solved; w++) {
                    bool taken = false;
                    for (int k = 0; k < count; k++) {
                        if (k == j) continue;
                        if (sections[k]->getVenue() == sections[j]->getVenue() &&
                            sections[k]->getTimeSlot() == TIME_WINDOWS[w]) {
                            taken = true; break;
                        }
                    }
                    if (!taken) {
                        cout << "  SUGGESTION: Move section "
                            << sections[j]->getSectionID()
                            << " to [" << TIME_WINDOWS[w] << "]\n";
                        solved = true;
                    }
                }
                if (!solved)
                    cout << "  SUGGESTION: No free slot found at this venue."
                    << " Consider a different venue.\n";

                anyConflict = true;
            }
        }
    }

    if (!anyConflict)
        cout << "No scheduling conflicts found.\n";

    cout << "=====================================\n";
    return anyConflict;
}
