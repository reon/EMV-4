#ifndef EMV_H
#define EMV_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

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

//    static QUrl GetURL() { return QUrl("http://service.iris.edu/fdsnws/event/1/query"); }
//    static QUrl GetURL() { return QUrl("http://www.google.com"); }

private slots:
    void Test_1_IRIS_Request();
    void Test_2_ISTI_mole_Request();

    //Network
    void FDSNRequest(QUrl url);

    void ReplyFinished(QNetworkReply* response);

    void LoadNewEvents(QVector<QuakeMLEvent> events);



    void on_actionLoad_XML_triggered();

    void on_actionOpen_FDSN_Request_Dialong_triggered();

private:
    Ui::EMV *ui;
    QNetworkAccessManager net;

    QVector<QuakeMLEvent> events;

    EventLayer* eventLayer {};

    Marble::GeoDataDocument* geoDoc {new Marble::GeoDataDocument};



    void SaveXML(QString xmlResponse); ///< For testing, Save XML on ReplayFinished()
    void ReloadGeoDocument();

};

#endif // EMV_H
