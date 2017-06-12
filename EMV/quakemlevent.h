#ifndef QUAKEMLEVENT_H
#define QUAKEMLEVENT_H

#include <QString>

#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>

class QuakeMLEvent
{
public:
    QString time;

    QString longitude;
    QString latitude;

    QString magnitude;

    //For conversion to Marble Types
    Marble::GeoDataCoordinates Point() const;
};


#endif // QUAKEMLEVENT_H
