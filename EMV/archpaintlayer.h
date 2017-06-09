#ifndef ARCHPAINTLAYER_H
#define ARCHPAINTLAYER_H

#include <QObject>
#include <marble/MarbleWidget.h>
#include <marble/MarbleMap.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>
#include <QtGui/QKeyEvent>
#include "archcolors.h"


//! Draws Archs linking an Event to
//! a List of Stations on a Marble Widget
/*!
   Requires a MarbleWidget, station locations
   and event location as input
*/



//TODO get rid of namespace
using namespace Marble;

//TODO move to own class
class archPaintLayer : public QObject, public LayerInterface
{
public:
    archPaintLayer(MarbleWidget* widget, QList<Marble::GeoDataCoordinates*> stations,
                Marble::GeoDataCoordinates* eventcoors);


    /** Implemented from LayerInterface */
    virtual QStringList renderPosition() const;

    /** Implemented from LayerInterface */
    virtual bool render( GeoPainter *painter, ViewportParams *viewport,
       const QString& renderPos = "NONE", GeoSceneLayer * layer = 0 );

    /** Overriding QObject */
    virtual bool eventFilter(QObject *obj, QEvent *event);

    /** Conversion tool */
    GeoDataCoordinates approximate(const GeoDataCoordinates &base, qreal angle, qreal dist) const;

private:
    MarbleWidget* m_widget; /*!< Marble Widget to draw on */
    QList<Marble::GeoDataCoordinates*> _stations; /*!< station locations to draw to */
    Marble::GeoDataCoordinates* _eventcoors; /*!< event location to draw from */

    int m_index;
};

#endif // ARCHPAINTLAYER_H
