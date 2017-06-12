#include "eventlayer.h"

using namespace Marble;
EventLayer::EventLayer(Marble::MarbleWidget* marbleWidget) : QObject(marbleWidget), mWidget{marbleWidget}
{

}

QStringList EventLayer::renderPosition() const
{
    return QStringList() << "HOVERS_ABOVE_SURFACE";
}

bool EventLayer::render( GeoPainter *painter, ViewportParams *viewport,
   const QString& renderPos, GeoSceneLayer * layer)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    if (events.isEmpty())
        return true;


    painter->setPen( QPen(QBrush(QColor::fromRgb(255,10,10,200)), 10.0, Qt::SolidLine, Qt::RoundCap ) );
    for (auto event : events) {
        painter->drawEllipse(
            GeoDataCoordinates(event.longitude.toFloat(), event.latitude.toFloat(), 0, GeoDataCoordinates::Degree),
            30.0f, 30.0f);
//        painter->drawPoint(
//            GeoDataCoordinates(event.longitude.toFloat(), event.latitude.toFloat(), 0, GeoDataCoordinates::Degree));
    }

    return true;
}
