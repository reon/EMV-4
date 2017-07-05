#include <mapwidget.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/MarbleModel.h>
#include <marble/GeoDataTreeModel.h>

#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

#include <marble/MarbleWidget.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include <marble/AbstractFloatItem.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataLineString.h>


MapWidget::MapWidget(QWidget *parent)
    : Marble::MarbleWidget(parent)
{


    //setMapThemeId("earth/plain/plain.dgml");
    setMapThemeId("earth/openstreetmap/openstreetmap.dgml");

    //Set Default Marble settings
    centerOn(8.4, 49.0);

    setShowCities(false);
    setShowPlaces(false);
    setShowOtherPlaces(false);
    setShowBackground(false);
    setShowBorders(false);

    setShowGrid(true);

    setShowCrosshairs(true);

    // Set the map quality to gain speed
    setMapQualityForViewContext( Marble::PrintQuality, Marble::Still );
    setMapQualityForViewContext( Marble::LowQuality, Marble::Animation );
}
