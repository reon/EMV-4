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
        on_action_EW_Initialize_triggered();
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

    QUrl url {settings.value("EW/MoleURL", "http://love.isti.com:8089/mole").toString()};
    QString query {"minmag=0&limit=200&orderby=mag&"};

    int TimeValue = settings.value("EW/TimeAmount", 60).toInt();
    QString TimeUnit = settings.value("EW/TimeUnit", "Minutes").toString();

    if (TimeUnit == "Hours") TimeValue *= 60;
    if (TimeUnit == "Days") TimeValue *= 24 * 60;

//    QTime range(0, TimeValue);

    QDateTime dateTimeStart = QDateTime::currentDateTime().addSecs(-1 * 60 * TimeValue);
    QDateTime dateTimeEnd = QDateTime::currentDateTime();

    dateTimeStart = dateTimeStart.toUTC();
    dateTimeEnd = dateTimeEnd.toUTC();

//    QString startTime = dateTimeStart.toString("yyyy-MM-dd") + "T" + "00:00:00" /*dateTimeStart.toString("hh:mm:ss")*/;
//    QString endTime = dateTimeEnd.toString("yyyy-MM-dd") + "T" + "23:59:59" /* dateTimeEnd.toString("hh:mm:ss")*/;

    QString startTime = dateTimeStart.toString("yyyy-MM-dd") + "T" + dateTimeStart.toString("hh:mm:ss");
    QString endTime = dateTimeEnd.toString("yyyy-MM-dd") + "T" + dateTimeEnd.toString("hh:mm:ss");

    query += "start=" + startTime + "&";
    query += "end=" + endTime;

    url.setQuery(QUrlQuery(query));

    qDebug() << url.toString() << "\n";

    /*emit*/ FDSNRequest(url);
}

/// Loads QuakeML .xml file into QVector<QuakeMLEvents> events
void EMV::on_action_Load_XML_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open XML"), QDir::homePath(), tr("XML Files (*.xml)"));

    if (fileName.isNull()) return;

    QFile in(fileName);

    if (!in.open(QIODevice::ReadOnly))
        return;

    QTextStream textIn(&in);
    QString XML = textIn.readAll();

    /*emit*/ LoadNewQuakeML(XML);
}


/// Open FDSN Dialog, show if already open
void EMV::on_action_Open_FDSN_Request_Dialog_triggered()
{
    using Coords = Marble::GeoDataCoordinates;

    if (!fdsnDialog)
    {
        Coords coords = ui->map->focusPoint();
        fdsnDialog = new FDSNRequestDialog{this, coords.latitude(Coords::Degree), coords.longitude(Coords::Degree)};
        connect(fdsnDialog, &FDSNRequestDialog::NewFDSNResponse, this, &EMV::LoadNewQuakeML);
        connect(this, &EMV::LatLongChanged, fdsnDialog, &FDSNRequestDialog::onUpdateCoords);
    }

    fdsnDialog->show();
}

void EMV::on_action_Settings_triggered()
{
//    if (!settingsDialog) {
//        settingsDialog = new Settings();
//    }
//    settingsDialog->show();

//    EW_Settings ewSettings(this);
//    ewSettings.exec();
    EarthWormSettings ewsettings;
    ewsettings.exec();
}


void EMV::on_action_Exit_triggered()
{
    QApplication::quit();
}

void EMV::on_action_EW_Initialize_triggered()
{
    EWC::StartImportGeneric();
}
