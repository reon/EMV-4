#include "quakemlevent.h"

//QuakeMLEvent::QuakeMLEvent()
//{

//}

using namespace Marble;

Marble::GeoDataCoordinates QuakeMLEvent::Point() const
{
    return GeoDataCoordinates(longitude.toFloat(), latitude.toFloat(), 0, GeoDataCoordinates::Degree);
}

Marble::GeoDataPlacemark QuakeMLEvent::Placemark() const
{
    GeoDataPlacemark placemark(this->name);
    placemark.setCoordinate(Point());
    placemark.setPopularity(9000);
    placemark.setVisualCategory(GeoDataPlacemark::GeoDataVisualCategory::Bookmark);

    return placemark;
}
