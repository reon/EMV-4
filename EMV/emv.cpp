//#include <memory>


#include "emv.h"
#include "ui_emv.h"


EMV::EMV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EMV),
    net{this}
{
    ui->setupUi(this);

    //Size the two main widgets, with table being smaller
    ui->splitter->setSizes(QList<int>{100, 400});

    eventLayer = new EventLayer(ui->map, &events);
    ui->map->addLayer(eventLayer);

    connect(ui->actionTest_1, SIGNAL(triggered(bool)), this, SLOT(Test_1_IRIS_Request()));
    connect(ui->actionTest_2, SIGNAL(triggered(bool)), this, SLOT(Test_2_ISTI_mole_Request()));

    connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));
}

EMV::~EMV()
{
    delete geoDoc;

    if (eventLayer) delete eventLayer;

    delete ui;
}

void EMV::Test_1_IRIS_Request()
{
    QUrl url {"http://service.iris.edu/fdsnws/event/1/query"};
    QString query {"minmag=5&limit=200&maxlat=38.101&minlon=-105.64100000000002&minlat=36.099&maxlon=-103.769&orderby=time"};

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

    if (response->error() != QNetworkReply::NoError) return;

    QByteArray bytes = response->readAll();
    QString XMLstring = QString(bytes);

    QuakeMLReader qxml(XMLstring);

    emit LoadNewEvents(qxml.events);
}

void EMV::LoadNewEvents(QVector<QuakeMLEvent> newEvents)
{
//    this->events = qxml.events;
    events += newEvents;

    ui->map->centerOn(events[0].longitude.toFloat(), events[0].latitude.toFloat(), true);
}


///Old
//void EMV::LoadEvents(QVector<QuakeMLEvent> events)
//{
//    using namespace Marble;

//    ui->map->model()->treeModel()->removeDocument(geoDoc);
//    geoDoc->clear();

//    for (QuakeMLEvent event : events)
//    {
//        auto placemark = new GeoDataPlacemark("event");
//        //placemarkers.append(placemark);

//        placemark->setCoordinate(event.longitude.toFloat(), event.latitude.toFloat(), 0, GeoDataCoordinates::Degree);
//        placemark->setPopulation(777);
//        placemark->setVisualCategory(Marble::GeoDataPlacemark::GeoDataVisualCategory::Bookmark);

//        geoDoc->append(placemark);

//    }
//    ui->map->centerOn(events[0].longitude.toFloat(), events[0].latitude.toFloat(), true);
//    ui->map->model()->treeModel()->addDocument(geoDoc);
//}



