#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

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
#include "MarbleLayers/archpaintlayer.h"


class MapWidget : public Marble::MarbleWidget
{
    Q_OBJECT

public:
//    explicit MapWidget();
    explicit MapWidget( QWidget *parent = 0 );
//    explicit MapWidget(/*QList<Plot*> *plotList*/)


    double slat;
    double slon;
    bool eventFlag;

    QList<Marble::GeoDataCoordinates*> stations;
    Marble::GeoDataCoordinates* eventcoors;
//    archPaintLayer* layer;

//    MapWidget(QList<Plot *> *plotList);
    Marble::GeoDataDocument *document;
//    virtual void customPaint(Marble::GeoPainter* painter);

public slots:
//    void updateData();


private:
//  QList<Plot *> *_plotList;
};

#endif // MAPWIDGET_H
