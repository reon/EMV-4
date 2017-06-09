#include "mapwidget.h"
#include "marble/GeoDataDocument.h"
#include "marble/GeoDataPlacemark.h"
#include "marble/MarbleModel.h"
#include "marble/GeoDataTreeModel.h"

#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

#include <marble/MarbleWidget.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include "marble/AbstractFloatItem.h"
#include <marble/GeoPainter.h>
#include <marble/GeoDataLineString.h>





MapWidget::MapWidget(QWidget *parent)
    : Marble::MarbleWidget(parent)
{


}


//MapWidget::MapWidget(QList<Plot*> *plotList)
//{

//    _plotList = plotList;



//    setMapThemeId("earth/plain/plain.dgml");

//    //make some kind of default
//    centerOn(8.4, 49.0);

//    setShowCities(false);
//    setShowPlaces(false);
//    setShowOtherPlaces(false);
//    setShowBackground(false);
//    setShowBorders(false);
//    setShowGrid(false);
//    //setShowTerrain(false);

//    foreach (Marble::AbstractFloatItem * floatItem, floatItems())
//    {

//      if (floatItem && (//floatItem->nameId() == "overviewmap" ||
//                        floatItem->nameId() == "compass")) //||
//                        //floatItem->nameId() == "navigation"))
//        floatItem->setVisible(false);
//    }


//    //TODO, create a button and make configurable
//    //setProjection( Mercator );

//    // Set the map quality to gain speed
//    setMapQualityForViewContext( Marble::NormalQuality, Marble::Still );
//    setMapQualityForViewContext( Marble::LowQuality, Marble::Animation );

//   // Center the map onto a given position
//   // Marble::GeoDataCoordinates home(-60.0, -10.0, 0.0, Marble::GeoDataCoordinates::Degree);
//   // mapWidget->centerOn(home);

//    document = new Marble::GeoDataDocument;

//    updateData();






//}

void MapWidget::updateData()
{



//    double rlat;
//    double rlon;
    eventFlag = false;
//    Marble::GeoDataPlacemark *event;
//    Marble::GeoDataCoordinates *coors;




    if(stations.length() > 0)
        stations.clear();

     this->model()->treeModel()->removeDocument( document );
     document->clear();



    //Puts all station in the satation list to the map
//    for(int i=0; i< _plotList->length();i++)
//    {
//        rlat = _plotList->at(i)->data->sac_base.header.stla;
//        rlon = _plotList->at(i)->data->sac_base.header.stlo;


//        Marble::GeoDataPlacemark *place = new Marble::GeoDataPlacemark(_plotList->at(i)->station);

//        coors = new Marble::GeoDataCoordinates(rlon, rlat, 0.0, Marble::GeoDataCoordinates::Degree);
//        stations.append(coors);
//        place->setCoordinate(rlon, rlat, 0.0, Marble::GeoDataCoordinates::Degree);

//        place->setPopulation( 666 );


//        place->setVisualCategory(Marble::GeoDataPlacemark::GeoDataVisualCategory::Volcano);



//        document->append( place );


//        //TODO change if condition to a flag
//        if(_plotList->at(i)->data->eventLat != -12345 && _plotList->at(i)->data->eventLong != -12345 && i ==0 )
//        {

//              slat = _plotList->at(i)->data->eventLat;
//              slon = _plotList->at(i)->data->eventLong;
//              eventFlag = true;


//              event = new Marble::GeoDataPlacemark();
//              eventcoors = new Marble::GeoDataCoordinates(slon, slat, 0.0, Marble::GeoDataCoordinates::Degree);
//              event->setCoordinate(slon, slat, 0.0, Marble::GeoDataCoordinates::Degree);
//              event->setPopulation( 666666 );

//              //TODO increase the size of the icon
//              event->setVisualCategory(Marble::GeoDataPlacemark::GeoDataVisualCategory::Bookmark);



//             // Marble::GeoDataDocument *document = new Marble::GeoDataDocument;
//              document->append( event );


//              // Add the document to MarbleWidget's tree model
//            //  model()->treeModel()->addDocument( document );


//              centerOn(slon, slat);

//        }

//    }


    this->model()->treeModel()->addDocument( document );
    this->removeLayer(layer);
    layer = new archPaintLayer(this,stations,eventcoors);
    // Uncomment for older versions of Marble:
    // mapWidget->map()->model()->addLayer(layer);
    this->addLayer(layer);
    // Install an event handler: Pressing + will change the layer we paint at
    this->installEventFilter(layer);




}

//void MapWidget::customPaint(Marble::GeoPainter* painter)
//{


//   //TODO make this more genaric (can I move this into the ctor?)
//   //Draw event label
//    Marble::GeoDataCoordinates home(_plotList->at(0)->data->eventLong, _plotList->at(0)->data->eventLat, 0.0, Marble::GeoDataCoordinates::Degree);
//    painter->drawText(home,_plotList->at(0)->data->eventName,-15,-17,200,200);





//}
