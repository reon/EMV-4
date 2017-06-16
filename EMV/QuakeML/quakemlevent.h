#ifndef QUAKEMLEVENT_H
#define QUAKEMLEVENT_H

#include <QString>

#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>

class QuakeMLEvent
{
public:
    QString name {"event"};
    QString id;
    QString dateTime;

    QString longitude;
    QString latitude;
    QString depth;

    QString magnitude;
    QString magnitudeType;

    bool operator==(const QuakeMLEvent& right);

    //For conversion to Marble Types
    Marble::GeoDataCoordinates Point() const;
    Marble::GeoDataPlacemark Placemark() const;

};


#endif // QUAKEMLEVENT_H
