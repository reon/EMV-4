#ifndef MAPWIDGET_H
#define MAPWIDGET_H
#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
//#include "plot.h"

#include <marble/MarbleWidget.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include "marble/AbstractFloatItem.h"
#include <marble/GeoPainter.h>
#include "archpaintlayer.h"


class MapWidget : public Marble::MarbleWidget
{
    Q_OBJECT

public:
    double slat;
    double slon;
    QList<Marble::GeoDataCoordinates*> stations;
    bool eventFlag;
    Marble::GeoDataCoordinates* eventcoors;
    archPaintLayer* layer;
    MapWidget();
//    MapWidget(QList<Plot *> *plotList);
    Marble::GeoDataDocument *document;
//    virtual void customPaint(Marble::GeoPainter* painter);

public slots:
    void updateData();


private:
//  QList<Plot *> *_plotList;
};

#endif // MAPWIDGET_H
