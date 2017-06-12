#include "quakemlevent.h"

//QuakeMLEvent::QuakeMLEvent()
//{

//}

using Marble::GeoDataCoordinates;

Marble::GeoDataCoordinates QuakeMLEvent::Point() const
{
    return GeoDataCoordinates(longitude.toFloat(), latitude.toFloat(), 0, GeoDataCoordinates::Degree);
}
