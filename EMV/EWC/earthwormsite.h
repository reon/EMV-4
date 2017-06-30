#ifndef EARTHWORMSITE_H
#define EARTHWORMSITE_H

#include <algorithm>
#include <stdexcept>

#include <QDebug>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QIODevice>
#include <QTextStream>

// For conversion
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>

/// Simple class for a Seismic station. Currently parses older EarthWorm format.

class EarthWormSite
{
public:
    EarthWormSite(QString line);
    EarthWormSite() = default;

    //Converts earthworm coords
    QString ProcessLatLong(const QString& integerPart, const QString& floatPart, const QString& direction);

    /// Used to read a list of stations from file
    static QVector<EarthWormSite> fromIODevice(QIODevice& io);

    Marble::GeoDataCoordinates Point() const;
    Marble::GeoDataPlacemark Placemark() const;
    QString SNCL() const;

private:

public:

    QString name;
    QString network;
    QString channel;
    QString location;
//    QString stationName;

    int channelID{};
    int index{};

    QString latitude {"0.0"};
    QString longitude {"0.0"};
    QString elevation{};


};

#endif // EARTHWORMSITE_H
