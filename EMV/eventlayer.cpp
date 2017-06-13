#include "eventlayer.h"

using namespace Marble;
EventLayer::EventLayer(Marble::MarbleWidget* marbleWidget, QVector<QuakeMLEvent>* events)
    : QObject(marbleWidget), mWidget{marbleWidget}, mEvents{events}
{

}

QStringList EventLayer::renderPosition() const
{
    return QStringList() << "HOVERS_ABOVE_SURFACE";
}



bool EventLayer::render( GeoPainter *painter, ViewportParams * /*viewport*/,
   const QString& /*renderPos*/, GeoSceneLayer * /*layer*/)
{
//    if (events.isEmpty())
//        return true;
    const qreal MAGNITUDE_MIN = 2.0;
    const qreal MAGNITUDE_FACTOR = 5.0;

    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen( QPen(QBrush(QColor::fromRgb(255,10,10,175)), 3.0, Qt::SolidLine, Qt::RoundCap ) );

    for (QuakeMLEvent event : *mEvents)
    {
        //Size circle based on magnitude
        qreal magnitude = event.magnitude.toDouble();
        magnitude = (magnitude > MAGNITUDE_MIN) ? magnitude : MAGNITUDE_MIN;
        magnitude *= MAGNITUDE_FACTOR;
        painter->drawEllipse(event.Point(), magnitude, magnitude);
    }

    return true;
}
