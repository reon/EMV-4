#ifndef EMV_H
#define EMV_H

#include <QObject>
#include <QPointer>
#include <QScopedPointer>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QSettings>

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

#include "EWC/earthwormsite.h"
#include "EWC/EarthWormComp.h"
#include "EWC/hypomessage.h"

#include "MarbleLayers/eventlayer.h"
#include "MarbleLayers/archpaintlayer.h"

#include "Dialogs/fdsnrequestdialog.h"
#include "Dialogs/earthwormsettings.h"



namespace Ui {
class EMV;
}

class EMV : public QMainWindow
{
    Q_OBJECT

public:
    explicit EMV(QWidget *parent = 0);
    ~EMV();

signals:
    void LatLongChanged(qreal latitude, qreal longitude);   // For sending coords to FDSNRequest Dialog

public slots:
    void on_HypoMessageReceived();

private slots:
    void on_Start();        //Operations that cannot/should not happen in constructor. Runs 0.5 sec after constructor

    //Network
    void Test_1_IRIS_Request();
    void Test_2_ISTI_mole_Request();

    void FDSNRequest(QUrl url);
    void ReplyFinished(QNetworkReply* response);

    void LoadNewQuakeML(QString xml);

    void on_GlobeMove();

    void on_tableWidget_itemSelectionChanged();

    void on_action_Load_XML_triggered();

    void on_action_Open_FDSN_Request_Dialog_triggered();

    void on_action_Exit_triggered();

    void on_action_EW_Initialize_triggered();

    void on_action_Settings_triggered();

    void on_action_Test_Hypo_Message_triggered();

private:
    void ConnectSlots();
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

    QSettings settings;

};

#endif // EMV_H
