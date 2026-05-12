



#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Section.h"
#include "Venue.h"

class Scheduler {

public:

    // Fixed: takes all sections + count so it can check real venue/timeslot conflicts
    bool schedule(
        Section* section,
        Venue venues[],
        int venueCount,
        Section* allSections[],
        int sectionCount
    );

    bool isConflict(Section* s1, Section* s2);

    void generateSchedule(
        Section* sections[],
        int sectionCount,
        Venue venues[],
        int venueCount
    );

    void exportSchedule(string fileName);
};

#endif