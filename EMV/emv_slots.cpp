#include "emv.h"
#include "ui_emv.h"

// ********************* SLOTS ***********************

void EMV::on_Start()
{
    static bool runOnce = false;

    if (runOnce) {
        qCritical() << "on_Start() ran more then once \n";
        return;
    }

    //No connect on start up if Q_DEBUG
    #ifndef Q_DEBUG
    if (settings.value("start/EWHypo", false).toBool())
        on_action_EW_Test_Initialize_triggered();
    #endif

    runOnce = true;
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
    int row = ui->tableWidget->currentRow();

    qreal latitude = ui->tableWidget->item(row,2)->text().toDouble();
    qreal longitude = ui->tableWidget->item(row, 3)->text().toDouble();

    ui->map->centerOn(longitude, latitude);
    ui->map->setZoom(2100);

    archLayer->SetEvent(Marble::GeoDataCoordinates(longitude, latitude, 0, Marble::GeoDataCoordinates::Degree));
    archLayer->SetShow(true);
}

//Test function, ugly
void EMV::on_HypoMessageReceived()
{

    events.clear();

    #ifdef Q_DEBUG
    QMessageBox::information(this, "Hypo Message", "Message Received, starting FDSN request.");
    #endif

    QUrl url {"http://love.isti.com:8089/mole"};
    QString query {"minmag=0&limit=200&orderby=mag&"};

    QDateTime dateTimeStart = QDateTime::currentDateTime()/*.addSecs(-3600)*/;
    QDateTime dateTimeEnd = QDateTime::currentDateTime();

    dateTimeStart = dateTimeStart.toUTC();
    dateTimeEnd = dateTimeEnd.toUTC();

    QString startTime = dateTimeStart.toString("yyyy-MM-dd") + "T" + "00:00:00" /*dateTimeStart.toString("hh:mm:ss")*/;
    QString endTime = dateTimeEnd.toString("yyyy-MM-dd") + "T" + "23:59:59" /* dateTimeEnd.toString("hh:mm:ss")*/;

//    QString startTime = dateTimeStart.toString("yyyy-MM-dd") + "T" + dateTimeStart.toString("hh:mm:ss");
//    QString endTime = dateTimeEnd.toString("yyyy-MM-dd") + "T" + dateTimeEnd.toString("hh:mm:ss");

//    QString startTime = GenerateDateTimeFragment(ui->StartDateTimeEdit->dateTime().toUTC());
//    QString endTime = GenerateDateTimeFragment(ui->EndDateTimeEdit->dateTime().toUTC());

    query += "start=" + startTime + "&";
    query += "end=" + endTime;

    url.setQuery(QUrlQuery(query));

    qDebug() << url.toString() << "\n";

    emit FDSNRequest(url);
}

/// Loads QuakeML .xml file into QVector<QuakeMLEvents> events
void EMV::on_action_Load_XML_triggered()
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


/// Open FDSN Dialog, show if already open
void EMV::on_action_Open_FDSN_Request_Dialong_triggered()
{
    using Coords = Marble::GeoDataCoordinates;

    if (!fdsnDialog)
    {
        Coords coords = ui->map->focusPoint();
        fdsnDialog = new FDSNRequestDialog{this, coords.latitude(Coords::Degree), coords.longitude(Coords::Degree)};
        connect(fdsnDialog, &FDSNRequestDialog::NewFDSNResponse, this, &EMV::LoadNewQuakeML);
        connect(this, &EMV::LatLongChanged, fdsnDialog, &FDSNRequestDialog::onUpdateCoords);

//        connect(fdsnDialog, SIGNAL(NewFDSNResponse(QString)), this, SLOT(LoadNewQuakeML(QString)));
//        connect(this, SIGNAL(LatLongChanged(qreal,qreal)), fdsnDialog, SLOT(onUpdateCoords(qreal, qreal)));
    }

    fdsnDialog->show();
}

void EMV::on_action_Exit_triggered()
{
    QApplication::quit();
}

void EMV::on_action_EW_Test_Initialize_triggered()
{
    EWC::StartImportGeneric();

   // QMessageBox::information(this, "EWC::StartImportGeneric()", QString::number(result));
}

void EMV::on_action_Connect_on_Startup_changed()
{
    settings.setValue("start/EWHypo", ui->action_Connect_on_Startup->isChecked());

}