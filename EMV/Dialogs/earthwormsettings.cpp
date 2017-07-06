#include "earthwormsettings.h"
#include "ui_earthwormsettings.h"

EarthWormSettings::EarthWormSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EarthWormSettings)
{
    ui->setupUi(this);

    ui->EW_Startup_Connect->setChecked(qsettings.value("EW/autostart", false).toBool());
    ui->EarthWormIP->setText(qsettings.value("EW/IP", "").toString());
    ui->EarthWormPort->setText(qsettings.value("EW/Port", "").toString());

    ui->MoleDBUrl->setText(qsettings.value("EW/MoleURL","").toString());

    ui->TimeAmountSelect->setValue(qsettings.value("EW/TimeAmount", 0).toInt());

    QString TimeUnit = qsettings.value("EW/TimeUnit", "").toString();
    ui->TimeUnitSelect->setCurrentText(TimeUnit);

    ui->ZoomLevel->setText(qsettings.value("EW/ZoomOnResponse", "").toString());

    ui->EarthWormImportFile->setText(qsettings.value("EW/ImportFile", "").toString());
}

EarthWormSettings::~EarthWormSettings()
{
    delete ui;
}

void EarthWormSettings::closeEvent(QCloseEvent *)
{
    //Autostart
    qsettings.setValue("EW/autostart", ui->EW_Startup_Connect->isChecked());

    //IP
    QString IP = ui->EarthWormIP->text().trimmed();
    if (IP.isEmpty())
        qsettings.remove("EW/IP");
    else
        qsettings.setValue("EW/IP", IP);

    //Port
    QString Port = ui->EarthWormPort->text().trimmed();
    if (Port.isEmpty())
        qsettings.remove("EW/Port");
    else
        qsettings.setValue("EW/Port", ui->EarthWormPort->text());

    //MoleURL
    QString URL = ui->MoleDBUrl->text().trimmed();
    if (URL.isEmpty())
        qsettings.remove("EW/MoleURL");
    else
        qsettings.setValue("EW/MoleURL", URL);

    //Time
    qsettings.setValue("EW/TimeAmount", ui->TimeAmountSelect->text().trimmed());
    qsettings.setValue("EW/TimeUnit", ui->TimeUnitSelect->currentText().trimmed());

    //Zoom
    QString ZoomLevel = ui->ZoomLevel->text().trimmed();
    if (ZoomLevel.isEmpty())
        qsettings.remove("EW/ZoomOnResponse");
    else
        qsettings.setValue("EW/ZoomOnResponse", ZoomLevel);

    QString ImportFile = ui->EarthWormImportFile->text().trimmed();
    if (ImportFile.isEmpty())
        qsettings.remove("EW/ImportFile");
    else
        qsettings.setValue("EW/ImportFile", ImportFile);
}

void EarthWormSettings::on_pushButton_clicked()
{
    QString value = QFileDialog::getOpenFileName(this, tr("Open Files"), QDir::homePath());
    if (!value.isNull())
        ui->EarthWormImportFile->setText(value);

}
