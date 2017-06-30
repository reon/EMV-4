#include "earthwormsite.h"

EarthWormSite::EarthWormSite(QString line)
{
    QStringList list = line.split(' ', QString::SkipEmptyParts);
    if (list.count() < 9)
        qDebug() << "EarthWormSite(): Invalid Line\n  :  " << line;

    //Seperate direction from number
    constexpr int LongFloatIndex = 6;
    QString LongFloatLine = list.takeAt(LongFloatIndex);
    list.insert(LongFloatIndex, LongFloatLine.right(1));    // Direction
    list.insert(LongFloatIndex, LongFloatLine.remove(LongFloatLine.length()-1,1));    // Number

    // Seperate number_DIRECTION_otherNumber
    constexpr int FusedLineIndex = 4; //Part of latitude and longitude are together, without a space ...
    QString FusedLine = list.takeAt(FusedLineIndex);
    int charIndex = std::max(FusedLine.indexOf('N'), FusedLine.indexOf('S'));
    list.insert(FusedLineIndex, FusedLine.left(charIndex));
    list.insert(FusedLineIndex + 1, FusedLine.mid(charIndex, 1));
//    list.insert(FusedLineIndex + 2, FusedLine.mid(charIndex+1));

    name = list[0];
    network = list[1];
    channel = list[2];

    latitude = ProcessLatLong(list[3], list[4], list[5]);
    longitude = ProcessLatLong(list[6], list[7], list[8]);

    elevation = list[9];
}


QVector<EarthWormSite> EarthWormSite::fromIODevice(QIODevice& io)
{
    QTextStream text(&io);
    QVector<EarthWormSite> list;

    while (!text.atEnd())
        list.append(EarthWormSite(text.readLine()));

    return list;
}

QString EarthWormSite::ProcessLatLong(const QString& integerPart, const QString& floatPart, const QString& direction)
{
    double coord = integerPart.toDouble() + (floatPart.toDouble() / 60.0);
    if (direction == "S" || direction == "W")
        coord = -coord;

    return QString::number(coord);
}

Marble::GeoDataCoordinates EarthWormSite::Point() const
{
    return Marble::GeoDataCoordinates(
        longitude.toFloat(), latitude.toFloat(), 0, Marble::GeoDataCoordinates::Degree);
}

Marble::GeoDataPlacemark EarthWormSite::Placemark() const
{
    using namespace Marble;
    GeoDataPlacemark placemark(this->name);
    placemark.setCoordinate(Point());
    placemark.setPopularity(9000);
    placemark.setVisualCategory(GeoDataPlacemark::GeoDataVisualCategory::Bookmark);

    return placemark;
}

QString EarthWormSite::SNCL() const
{
    return name + "." + network + "." + channel;

}
