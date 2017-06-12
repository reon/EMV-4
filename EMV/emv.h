#ifndef EMV_H
#define EMV_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QtNetwork/qnetworkaccessmanager.h>

#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/MarbleModel.h>
#include <marble/GeoDataTreeModel.h>

#include "quakemlreader.h"
#include "quakemlevent.h"
#include "eventlayer.h"

namespace Ui {
class EMV;
}

class EMV : public QMainWindow
{
    Q_OBJECT

public:
    explicit EMV(QWidget *parent = 0);
    ~EMV();

    static QUrl GetURL() { return QUrl("http://service.iris.edu/fdsnws/event/1/query"); }
//    static QUrl GetURL() { return QUrl("http://www.google.com"); }

private slots:
    void on_actionTest_1_Get_triggered();

    //Network
    void replyFinished(QNetworkReply* response);

    void LoadEvents(QVector<QuakeMLEvent> events);

private:
    Ui::EMV *ui;
    QNetworkAccessManager net;

    QVector<QuakeMLEvent> events;
    Marble::GeoDataDocument* geoDoc {new Marble::GeoDataDocument};

    EventLayer* eventLayer {};

};

#endif // EMV_H
