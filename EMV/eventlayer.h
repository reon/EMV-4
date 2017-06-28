#ifndef EVENTLAYER_H
#define EVENTLAYER_H

#include <QObject>
#include <QVector>

#include <marble/MarbleWidget.h>
#include <marble/MarbleMap.h>
#include <marble/GeoPainter.h>
#include <marble/LayerInterface.h>

#include "QuakeML/quakemlevent.h"


class EventLayer : public QObject, public Marble::LayerInterface
{
    Q_OBJECT
public:
    explicit EventLayer(Marble::MarbleWidget* marbleWidget, QVector<QuakeMLEvent>* events);

    // Implemented from LayerInterface
    virtual QStringList renderPosition() const;

    // Implemented from LayerInterface
    virtual bool render( Marble::GeoPainter *painter, Marble::ViewportParams *viewport,
       const QString& renderPos = "NONE", Marble::GeoSceneLayer * layer = 0 );

    // Overriding QObject
//    virtual bool eventFilter(QObject *obj, QEvent *event);



signals:

public slots:

private:
    Marble::MarbleWidget * mWidget;     //Not used
    QVector<QuakeMLEvent>* mEvents;     //Not owned

    int mIndex {};

};


#endif // EVENTLAYER_H
