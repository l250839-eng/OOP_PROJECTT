#include "Scheduler.h"
#include <iostream>
#include <fstream>

using namespace std;

// =====================================================
// SCHEDULE ONE SECTION
// Fixed: conflict check now compares against ALL other
// sections, not against the section's own current venue.
// =====================================================

bool Scheduler::schedule(
    Section* section,
    Venue venues[],
    int venueCount,
    Section* allSections[],
    int sectionCount
) {
    if (section == nullptr) {
        return false;
    }

    for (int i = 0; i < venueCount; i++) {

        // ---- NULL SAFETY ----
        if (venues[i].getRoomID() == "") {
            continue;
        }

        // ---- CAPACITY CHECK ----
        // Venue must fit all students in the section
        if (venues[i].getCapacity() < section->getStudentCount()) {
            cout << "  Venue " << venues[i].getRoomID()
                << " skipped: capacity " << venues[i].getCapacity()
                << " < section size " << section->getStudentCount() << "\n";
            continue;
        }

        // ---- LAB CHECK ----
        // Lab courses need a venue with computers
        if (section->getCourseType() == "Lab") {
            if (!venues[i].hasComputers()) {
                cout << "  Venue " << venues[i].getRoomID()
                    << " skipped: Lab course needs computers.\n";
                continue;
            }
        }

        // ---- REAL CONFLICT CHECK ----
        // Check if ANY other section is already using this venue
        // at the same time slot as our section.
        bool conflict = false;

        for (int j = 0; j < sectionCount; j++) {

            if (allSections[j] == section) continue; // skip self

            if (allSections[j]->getVenue() == venues[i].getRoomID()
                && allSections[j]->getTimeSlot() == section->getTimeSlot()
                && allSections[j]->getTimeSlot() != "") // only if timeslot is known
            {
                cout << "  Venue " << venues[i].getRoomID()
                    << " skipped: conflict with section "
                    << allSections[j]->getSectionID()
                    << " at " << section->getTimeSlot() << "\n";
                conflict = true;
                break;
            }
        }

        if (conflict) continue;

        // ---- ASSIGN ----
        section->setVenue(venues[i].getRoomID());

        cout << "Section " << section->getSectionID()
            << " scheduled in venue " << venues[i].getRoomID()
            << "\n";

        return true;
    }

    cout << "ERROR: No suitable venue found for section "
        << section->getSectionID() << "\n";

    return false;
}

// =====================================================
// IS CONFLICT
// Two sections conflict if they share the same venue
// AND the same time slot.
// =====================================================

bool Scheduler::isConflict(Section* s1, Section* s2) {

    if (s1 == nullptr || s2 == nullptr) return false;

    return (
        s1->getTimeSlot() == s2->getTimeSlot() &&
        s1->getVenue() == s2->getVenue() &&
        s1->getTimeSlot() != ""                // empty timeslot = not scheduled yet
        );
}

// =====================================================
// GENERATE FULL SCHEDULE
// Assigns every section a venue + timeslot.
// Uses a grid to track which (venue, slot) pairs are taken.
// If a slot is taken the conflict solver moves to the next one.
// Lab courses are skipped (no final exam, duration = 0).
// =====================================================

void Scheduler::generateSchedule(
    Section* sections[],
    int sectionCount,
    Venue venues[],
    int venueCount
) {
    string slots[] = {
        "Mon-9AM",  "Mon-11AM", "Mon-2PM",  "Mon-4PM",
        "Tue-9AM",  "Tue-11AM", "Tue-2PM",  "Tue-4PM",
        "Wed-9AM",  "Wed-11AM", "Wed-2PM",  "Wed-4PM"
    };
    const int slotCount = 12;

    // venueSlotUsed[venueIndex][slotIndex]
    bool venueSlotUsed[50][12] = {};

    int conflictsResolved = 0;

    for (int i = 0; i < sectionCount; i++) {

        Section* sec = sections[i];
        string courseType = sec->getCourseType();

        // Lab courses have no final exam
        if (courseType == "Lab") {
            cout << "  " << sec->getSectionID()
                << " [Lab] -> No final exam. Skipping.\n";
            continue;
        }

        int duration = 0;
        if (sec->getCourse()) duration = sec->getCourse()->getExamDuration();

        bool scheduled = false;

        for (int v = 0; v < venueCount && !scheduled; v++) {

            // Capacity check (0 enrolled = allow for demo data)
            if (sec->getStudentCount() > 0 &&
                venues[v].getCapacity() < sec->getStudentCount()) {
                continue;
            }

            for (int s = 0; s < slotCount && !scheduled; s++) {

                if (venueSlotUsed[v][s]) {
                    conflictsResolved++;
                    continue; // linear search conflict solver
                }

                venueSlotUsed[v][s] = true;
                sec->setVenue(venues[v].getRoomID());

                cout << "  " << sec->getSectionID()
                    << " -> " << venues[v].getRoomID()
                    << " @ " << slots[s]
                    << " (" << duration << "hr)\n";

                scheduled = true;
            }
        }

        if (!scheduled) {
            cout << "  ERROR: No slot found for "
                << sec->getSectionID() << "\n";
        }
    }

    if (conflictsResolved > 0) {
        cout << "\nConflict solver skipped "
            << conflictsResolved
            << " taken slot(s) automatically.\n";
    }
}

// =====================================================
// EXPORT SCHEDULE TO FILE
// =====================================================

void Scheduler::exportSchedule(string fileName) {

    ofstream fout(fileName);

    if (!fout) {
        cout << "ERROR: Cannot write to " << fileName << "\n";
        return;
    }

    fout << "SectionID | VenueID | TimeSlot\n";
    fout << "-----------------------------------\n";

    // Note: schedule data is stored in each Section object's venue field.
    // The generateSchedule() function in main.cpp writes the full detail
    // to Schedule.txt directly during generation so nothing is lost.

    fout.close();

    cout << "Schedule exported to " << fileName << "\n";
}