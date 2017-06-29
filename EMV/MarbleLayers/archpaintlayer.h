#ifndef ARCHPAINTLAYER_H
#define ARCHPAINTLAYER_H

#include <QObject>
#include <QtGui/QKeyEvent>

#include <marble/MarbleWidget.h>
#include <marble/MarbleMap.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>
#include <marble/GeoDataLineString.h>

#include "archcolors.h"


//! Draws Archs linking an Event to
//! a List of Stations on a Marble Widget
/*!
   Requires a MarbleWidget, station locations
   and event location as input
*/



//TODO get rid of namespace
//using namespace Marble;

//TODO move to own class
class ArchPaintLayer : public QObject, public Marble::LayerInterface
{
public:
//    ArchPaintLayer(Marble::MarbleWidget* widget, QList<Marble::GeoDataCoordinates*> stations,
//                Marble::GeoDataCoordinates* eventcoors);
    ArchPaintLayer(Marble::MarbleWidget* widget);


    /** Implemented from LayerInterface */
    virtual QStringList renderPosition() const;

    /** Implemented from LayerInterface */
    virtual bool render( Marble::GeoPainter *painter, Marble::ViewportParams *viewport,
       const QString& renderPos = "NONE", Marble::GeoSceneLayer * layer = 0 );

    /** Overriding QObject */
    virtual bool eventFilter(QObject *obj, QEvent *event);

    /** Conversion tool */
    Marble::GeoDataCoordinates approximate(const Marble::GeoDataCoordinates &base, qreal angle, qreal dist) const;

    void SetStations(QVector<Marble::GeoDataCoordinates> stations) { this->stations = stations; }
    void SetEvent(Marble::GeoDataCoordinates event) { this->eventCoords = event; }

    void SetShow(bool enabled = true) { this->enabled = enabled; }
private:
    bool enabled = false;

    Marble::MarbleWidget* m_widget; /*!< Not Used. Marble Widget to draw on */
    QVector<Marble::GeoDataCoordinates> stations; /*!< station locations to draw to */
    Marble::GeoDataCoordinates eventCoords; /*!< event location to draw from */

    int m_index;    // Currently unused, looks like user presses '+' -> index++;
};

#endif // ARCHPAINTLAYER_H
