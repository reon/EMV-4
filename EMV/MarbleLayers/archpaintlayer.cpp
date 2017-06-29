#include <QtGui/QKeyEvent>

//#include <marble/MarbleMap.h>
//#include <marble/GeoPainter.h>
//#include <marble/LayerInterface.h>
//#include <marble/GeoDataLineString.h>

#include "archpaintlayer.h"

using namespace Marble;

//ArchPaintLayer::ArchPaintLayer(MarbleWidget* widget,QList<Marble::GeoDataCoordinates*> stations,
//                           Marble::GeoDataCoordinates* eventcoors) : m_widget(widget), m_index(0)
//{
//    stations = stations;
//    eventCoords = eventcoors;
//}

ArchPaintLayer::ArchPaintLayer(MarbleWidget *widget)
    : QObject(widget), m_widget(widget)
{

}

QStringList ArchPaintLayer::renderPosition() const
{
    //Paint layers.
    QStringList layers = QStringList() << "SURFACE" << "HOVERS_ABOVE_SURFACE";
    layers << "ORBIT" << "USER_TOOLS" << "STARS";


    //int index = m_index % layers.size();
    return QStringList() << layers.at(2);
}

//unused example
bool ArchPaintLayer::eventFilter(QObject* /* obj*/, QEvent *event)
{
    // Adjust the current layer when '+' is pressed
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Plus) {
            ++m_index;
            return true;
        }
    }

    return false;
}


GeoDataCoordinates ArchPaintLayer::approximate(const GeoDataCoordinates &base, qreal angle, qreal dist) const
{
    // This is just a rough estimation that ignores projections.

    GeoDataCoordinates::Unit deg = GeoDataCoordinates::Degree;
    return GeoDataCoordinates ( base.longitude(deg) + 1.5 * dist * sin(angle),
                base.latitude(deg) + dist * cos(angle), 0.0, deg);
}

bool ArchPaintLayer::render( GeoPainter *painter, ViewportParams* /* viewport */,
    const QString& /*renderPos*/, GeoSceneLayer * /*layer*/ )
{
    if (!enabled) return true;

    // Have window title reflect the current paint layer
    m_widget->setWindowTitle(renderPosition().first());

    painter->setRenderHint(QPainter::Antialiasing, false);

    for(int i = 0; i< stations.length(); i++)
    {
        Marble::GeoDataLineString shapeLatitudeCircle( Marble::RespectLatitudeCircle | Marble::Tessellate );
        shapeLatitudeCircle << stations[i] << eventCoords;

        painter->setPen(QPen(QBrush(oxygenRed), 1.5));
        painter->drawPolyline( shapeLatitudeCircle );
    }

    return true;
}


