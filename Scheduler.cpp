#include "Scheduler.h"
#include "Section.h"
#include <iostream>

using namespace std;

void Scheduler::assignVenues(
    Section* sections[],
    int sectionCount,
    Venue venues[],
    int venueCount
)
{
    for (int i = 0; i < sectionCount; i++)
    {
        cout << "Section "
            << sections[i]->getSectionID()
            << " assigned successfully."
            << endl;
    }
}

bool Scheduler::checkConflict(
    Section* sections[],
    int count
)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (
                sections[i]->getVenue()
                ==
                sections[j]->getVenue()
                &&
                sections[i]->getTimeSlot()
                ==
                sections[j]->getTimeSlot()
                )
            {
                cout << "Conflict Found Between Sections: "
                    << sections[i]->getSectionID()
                    << " and "
                    << sections[j]->getSectionID()
                    << endl;

                return true;
            }
        }
    }

    cout << "No Conflicts Found."
        << endl;

    return false;
}
