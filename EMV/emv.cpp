#include "emv.h"
#include "ui_emv.h"

#include "EarthWormComp.h"

EMV::EMV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EMV),

    net{this}
{
    ui->setupUi(this);

    //Size the two main widgets, with table being smaller
    ui->splitter->setSizes(QList<int>{180, 400});

//    Marble::GeoDataCoordinates::setDefaultNotation(Marble::GeoDataCoordinates::Degree);
    eventLayer.reset(new EventLayer(ui->map, &events));
    ui->map->addLayer(eventLayer.data());

    LatitudeLabel->setFixedWidth(100);
    LongitudeLabel->setFixedWidth(100);

    ui->StatusBar->addPermanentWidget(LatitudeNameLabel);
    ui->StatusBar->addPermanentWidget(LatitudeLabel);
    ui->StatusBar->addPermanentWidget(LongitudeNameLabel);
    ui->StatusBar->addPermanentWidget(LongitudeLabel);

    connect(ui->action_IRIS_Test, SIGNAL(triggered(bool)), this, SLOT(Test_1_IRIS_Request()));
    connect(ui->action_ISTI_Test, SIGNAL(triggered(bool)), this, SLOT(Test_2_ISTI_mole_Request()));

    connect(ui->map, SIGNAL(visibleLatLonAltBoxChanged(GeoDataLatLonAltBox)),
        this, SLOT(on_GlobeMove()));

    connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));
}

EMV::~EMV()
{
    ui->map->model()->treeModel()->removeDocument(geoDoc.data());
//    delete geoDoc;

    ui->map->removeLayer(eventLayer.data());
    delete ui;
}

void EMV::on_GlobeMove()
{
    using Coords = Marble::GeoDataCoordinates;

    Coords coords = ui->map->focusPoint();
    LatitudeLabel->setText(QString::number(coords.latitude(Coords::Degree)));
    LongitudeLabel->setText(QString::number(coords.longitude(Coords::Degree)));

    emit LatLongChanged(coords.latitude(Coords::Degree), coords.longitude(Coords::Degree));
}

/// Move some of this to quakeMLTable
void EMV::on_tableWidget_itemSelectionChanged()
{
//    using Coords = Marble::GeoDataCoordinates;

    int row = ui->tableWidget->currentRow();

    qreal latitude = ui->tableWidget->item(row,2)->text().toDouble();
    qreal longitude = ui->tableWidget->item(row, 3)->text().toDouble();

    ui->map->centerOn(longitude, latitude);
}

void EMV::LoadNewQuakeML(QString xml)
{
    #ifdef QT_DEBUG
    SaveXML(xml);
    #endif

    QuakeMLReader qxml(xml);

    if (qxml.events.empty()) return;

    //Might need to move
    ui->map->centerOn(qxml.events[0].longitude.toFloat(), qxml.events[0].latitude.toFloat(), true);

    events += qxml.events;

    ReloadGeoDocument();

    ui->tableWidget->AddQuakeMLEvents(qxml.events);
}

/// For inspecting
void EMV::SaveXML(QString xmlResponse)
{
    if (!ui->actionSave_XML->isChecked())
        return;

    QFile out("XML Response at : " + QDateTime::currentDateTime().toString("hh:mm dd.MM") + ".xml", this);

    if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream textOut(&out);
    textOut << xmlResponse;
    textOut.flush();
    out.close();
}

/// Clears MarbleModel and reloads all QuakeMLEvents
void EMV::ReloadGeoDocument()
{
    using namespace Marble;

    ui->map->model()->treeModel()->removeDocument(geoDoc.data());
    geoDoc->clear();

    for (QuakeMLEvent event : events)
    {
        auto placemark = new GeoDataPlacemark("event");

        placemark->setCoordinate(event.longitude.toFloat(), event.latitude.toFloat(), 0, GeoDataCoordinates::Degree);
        placemark->setPopulation(777);
        placemark->setVisualCategory(GeoDataPlacemark::GeoDataVisualCategory::Bookmark);

        geoDoc->append(placemark);
    }

    ui->map->model()->treeModel()->addDocument(geoDoc.data());
}


/// Loads QuakeML .xml file into QVector<QuakeMLEvents> events
void EMV::on_actionLoad_XML_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open XML"), "/home/alex", tr("XML Files (*.xml)"));

    if (fileName.isNull()) return;

    QFile in(fileName);

    if (!in.open(QIODevice::ReadOnly))
        return;

    QTextStream textIn(&in);
    QString XML = textIn.readAll();

    emit LoadNewQuakeML(XML);
}

/// Network

/// Open FDSN Dialog, show if already open
void EMV::on_actionOpen_FDSN_Request_Dialong_triggered()
{
    using Coords = Marble::GeoDataCoordinates;

    if (!fdsnDialog)
    {
        Coords coords = ui->map->focusPoint();
        fdsnDialog = new FDSNRequestDialog{this, coords.latitude(Coords::Degree), coords.longitude(Coords::Degree)};
        connect(fdsnDialog, SIGNAL(NewFDSNResponse(QString)), this, SLOT(LoadNewQuakeML(QString)));
        connect(this, SIGNAL(LatLongChanged(qreal,qreal)), fdsnDialog, SLOT(onUpdateCoords(qreal, qreal)));
    }

    fdsnDialog->show();
}

void EMV::on_action_Exit_triggered()
{
    QApplication::quit();
}

void EMV::Test_1_IRIS_Request()
{
    QUrl url {"http://service.iris.edu/fdsnws/event/1/query"};
    QString query {"minmag=1&limit=50&maxlat=38.101&minlon=-105.64100000000002&minlat=36.099&maxlon=-103.769&orderby=time"};

    url.setQuery(QUrlQuery(query));

    emit FDSNRequest(url);
    //net.get(QNetworkRequest(url));
}

void EMV::Test_2_ISTI_mole_Request()
{
    QUrl url {"http://love.isti.com:8089/mole"};
    QString query {"minmag=2&limit=200&orderby=mag"};

    url.setQuery(QUrlQuery(query));
    emit FDSNRequest(url);
}


void EMV::FDSNRequest(QUrl url)
{
    net.get(QNetworkRequest(url));
}


void EMV::ReplyFinished(QNetworkReply* response)
{
    QString status = response->error()==QNetworkReply::NoError ? "Success" : "Error";
    QMessageBox::information(this, "Network response.", status);

    response->deleteLater();

    if (response->error() != QNetworkReply::NoError) {
        qDebug() << "Network error.\n";
        return;
    }

    QByteArray bytes = response->readAll();
    QString strResponse = QString(bytes);

    int httpCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (httpCode != 200)
    {
        QMessageBox::critical(this, "FDSN response", "Failed to retreive data \n Response: \n" + strResponse);
        return;
    }

    emit LoadNewQuakeML(strResponse);
}




void EMV::on_action_EW_Test_Initialize_triggered()
{
    EWC::StartImportGeneric();

   // QMessageBox::information(this, "EWC::StartImportGeneric()", QString::number(result));
}
