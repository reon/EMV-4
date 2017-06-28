#ifndef EMV_H
#define EMV_H

#include <QObject>
#include <QPointer>
#include <QScopedPointer>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QtNetwork/qnetworkaccessmanager.h>

#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataCoordinates.h>
#include <marble/MarbleModel.h>
#include <marble/GeoDataTreeModel.h>

#include "QuakeML/quakemlreader.h"
#include "QuakeML/quakemlevent.h"

#include "earthwormsite.h"

#include "eventlayer.h"
#include "archpaintlayer.h"

#include "Dialogs/fdsnrequestdialog.h"


#include "EarthWormComp.h"

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

signals:
    void LatLongChanged(qreal latitude, qreal longitude);


private slots:
    void Test_1_IRIS_Request();
    void Test_2_ISTI_mole_Request();

    //Network
    void FDSNRequest(QUrl url);
    void ReplyFinished(QNetworkReply* response);

    void LoadNewQuakeML(QString xml);

    void on_actionLoad_XML_triggered();

    void on_actionOpen_FDSN_Request_Dialong_triggered();

    void on_action_Exit_triggered();

    void on_GlobeMove();

    void on_tableWidget_itemSelectionChanged();

    void on_action_EW_Test_Initialize_triggered();

private:    
    void SaveXML(QString xmlResponse); ///< For testing, Save XML on ReplayFinished()
    void ReloadGeoDocument();

        //Members
private:
    Ui::EMV *ui;
        // Status bar labels
    QLabel* LatitudeNameLabel { new QLabel("Latitude : ", this) };
    QLabel* LatitudeLabel { new QLabel(this) };
    QLabel* LongitudeNameLabel { new QLabel("Longitude : ", this) };
    QLabel* LongitudeLabel { new QLabel(this) };

    QPointer<FDSNRequestDialog> fdsnDialog;

    QScopedPointer<EventLayer> eventLayer;
    QScopedPointer<ArchPaintLayer> archLayer;
    QScopedPointer<Marble::GeoDataDocument> geoDoc {new Marble::GeoDataDocument};

        //For test net code
    QNetworkAccessManager net;

    QVector<QuakeMLEvent> events;

    QVector<EarthWormSite> stations;


};

#endif // EMV_H
