



#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Section.h"
#include "Venue.h"

class Scheduler
{
public:

    void assignVenues(
        Section* sections[],
        int sectionCount,
        Venue venues[],
        int venueCount
    );

    bool checkConflict(
        Section* sections[],
        int count
    );
};

#endif
