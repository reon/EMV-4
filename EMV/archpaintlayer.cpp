#include "archpaintlayer.h"
#include <marble/MarbleMap.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>
#include <QtGui/QKeyEvent>
#include <marble/GeoDataLineString.h>




archPaintLayer::archPaintLayer(MarbleWidget* widget,QList<Marble::GeoDataCoordinates*> stations,
                           Marble::GeoDataCoordinates* eventcoors) : m_widget(widget), m_index(0)
{
    _stations = stations;
    _eventcoors = eventcoors;
}

QStringList archPaintLayer::renderPosition() const
{
    //Paint layers.
    QStringList layers = QStringList() << "SURFACE" << "HOVERS_ABOVE_SURFACE";
    layers << "ORBIT" << "USER_TOOLS" << "STARS";


    //int index = m_index % layers.size();
    return QStringList() << layers.at(2);
}

//unused example
bool archPaintLayer::eventFilter(QObject* /* obj*/, QEvent *event)
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


GeoDataCoordinates archPaintLayer::approximate(const GeoDataCoordinates &base, qreal angle, qreal dist) const
{
    // This is just a rough estimation that ignores projections.

    GeoDataCoordinates::Unit deg = GeoDataCoordinates::Degree;
    return GeoDataCoordinates ( base.longitude(deg) + 1.5 * dist * sin(angle),
                base.latitude(deg) + dist * cos(angle), 0.0, deg);
}

bool archPaintLayer::render( GeoPainter *painter, ViewportParams* /* viewport */,
    const QString& /*renderPos*/, GeoSceneLayer * /*layer*/ )
{
    // Have window title reflect the current paint layer
    m_widget->setWindowTitle(renderPosition().first());

    painter->setRenderHint(QPainter::Antialiasing, true);

    for(int i = 0; i< _stations.length(); i++)
     {

        Marble::GeoDataLineString shapeLatitudeCircle( Marble::RespectLatitudeCircle | Marble::Tessellate );
        shapeLatitudeCircle << *_stations[i] << *_eventcoors;

        painter->setPen(oxygenBrightBlue );
        painter->drawPolyline( shapeLatitudeCircle );

      }

    return true;
}


