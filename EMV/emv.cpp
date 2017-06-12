//#include <memory>


#include "emv.h"
#include "ui_emv.h"

#include "quakemlreader.h"

EMV::EMV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EMV),
    net{this}
{
    ui->setupUi(this);

    eventLayer = new EventLayer(ui->map);
    ui->map->addLayer(eventLayer);

    connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));


}

EMV::~EMV()
{
    delete geoDoc;

    if (eventLayer) delete eventLayer;

    delete ui;
}

void EMV::on_actionTest_1_Get_triggered()
{
//    QMessageBox::information(this, "Host", GetURL().host());
    QString rawQuery = "minmag=5&limit=200&maxlat=38.101&minlon=-105.64100000000002&minlat=36.099&maxlon=-103.769&orderby=time";
    QUrlQuery query(rawQuery);

    QUrl url = GetURL();
    url.setQuery(query);

    net.get(QNetworkRequest(url));
}

void EMV::replyFinished(QNetworkReply* response)
{
    QString status = response->error()==QNetworkReply::NoError ? "Success" : "Error";
    QMessageBox::information(this, "Network response.", status);

    response->deleteLater();

    if (response->error() != QNetworkReply::NoError) return;

    QByteArray bytes = response->readAll();
    QString XMLstring = QString(bytes);

    QuakeMLReader qxml(XMLstring);

    ///To be replaced with onNewEvents(QVector<QMLEvent>)
    this->events = qxml.events;
    //LoadEvents(qxml.events);
    eventLayer->events = events;

    ui->map->centerOn(events[0].longitude.toFloat(), events[0].latitude.toFloat(), true);
}


///Old
void EMV::LoadEvents(QVector<QMLEvent> events)
{
    using namespace Marble;

    ui->map->model()->treeModel()->removeDocument(geoDoc);
    geoDoc->clear();

    for (QMLEvent event : events)
    {
        auto placemark = new GeoDataPlacemark("event");
        //placemarkers.append(placemark);

        placemark->setCoordinate(event.longitude.toFloat(), event.latitude.toFloat(), 0, GeoDataCoordinates::Degree);
        placemark->setPopulation(777);
        placemark->setVisualCategory(Marble::GeoDataPlacemark::GeoDataVisualCategory::Bookmark);

        geoDoc->append(placemark);

    }
    ui->map->centerOn(events[0].longitude.toFloat(), events[0].latitude.toFloat(), true);
    ui->map->model()->treeModel()->addDocument(geoDoc);
}
